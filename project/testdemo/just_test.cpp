/*#include <eosiolib/eosio.hpp>
#include "Contract.hpp"
using namespace eosio;

class hello : public eosio::contract {
  public:
      using contract::contract;

      /// @abi action 
      void hi( account_name user ) {
         print( "Hello, ", name{user} );
         auto test_obj = Mediation::CContract();
      }
};

EOSIO_ABI( hello, (hi) )
*/

#include <eosiolib/eosio.hpp>
#include "Contract.hpp"
#include "ABIheader.hpp"

using namespace eosio;
using namespace std;
namespace eosio{
  static void capi_checksum256_to_checksum256(checksum256 &k, const capi_checksum256 &hash)
  {
    const uint128_t *p128 = reinterpret_cast<const uint128_t *>(&hash);
    //checksum256 k;
    k.data()[0] = p128[0];
    k.data()[1] = p128[1];
   // return k;
  }

  static checksum256 capi_checksum256_to_checksum256(const capi_checksum256 &hash)
  {
    const uint128_t *p128 = reinterpret_cast<const uint128_t *>(&hash);
    checksum256 k;
    k.data()[0] = p128[0];
    k.data()[1] = p128[1];
   return k;
  }
}
CONTRACT hello : public contract {
  TABLE test_table {
    uint64_t owner;
    uint64_t primary_key() const { return owner; }
  };
  TABLE ContractData {
    uint64_t creator;
    //uint64_t hash;// sha256(creator + content)
    capi_checksum256 hash;
    //checksum256 hash;
    string content;
    string UseInfo;///存储所有合约状态的索引

    uint64_t primary_key() const { return *((uint64_t*)&hash); }

    uint64_t get_creator() const {return creator; }
    checksum256 by_hash() const { return capi_checksum256_to_checksum256(hash); }//TODO

    //序列化
    //EOSLIB_SERIALIZE(ContractData, (creator)(hash)(content)(UseInfo));
  };

  TABLE ContractState {
      uint64_t Sponsor;
      uint64_t hash;// sha256(Sponsor + ContractData.hash + describe)
      string describe;
      string State;
      
      uint64_t primary_key() const { return hash; }
     
      uint64_t get_sponsor() const {return Sponsor; }
   
      //序列化
      EOSLIB_SERIALIZE(ContractState, (Sponsor)(hash)(describe)(State));
  };
  public:
  	using contract::contract;
    typedef eosio::multi_index< "testtab"_n, test_table > testtable_t;
    typedef eosio::multi_index< "contractdata"_n, ContractData,
            indexed_by< "creator"_n, const_mem_fun<ContractData, uint64_t, &ContractData::get_creator > >,
            indexed_by< "hash"_n, const_mem_fun<ContractData, checksum256, &ContractData::by_hash > >
            > ContractData_index;
    typedef eosio::multi_index< "contractstate"_n, ContractState,
            indexed_by<"sponsor"_n, const_mem_fun<ContractState, uint64_t, &ContractState::get_sponsor>>
            > ContractState_index;
    void init(){}
   	ACTION hi( name nm ) {
  		print_f("Name : %\n", nm);
 			auto test_obj = Mediation::CContract(_self);
      print(test_obj.SerializeByJson());
      capi_checksum256 hash;
      test_obj.GetHash(hash);
      ContractData_index storage_obj(_self, _self.value);
      auto creator_index = storage_obj.get_index<name("hash")>();

      auto itr = creator_index.find(capi_checksum256_to_checksum256(hash));
      //auto itr = creator_index.find(_self.value);
      if (itr != creator_index.end()){
        print("***exit***", _self.value);
    //    print(itr->content);
      }else{
        print("***insert***");
        storage_obj.emplace(_self, [&](auto& c){
          c.creator = _self.value;
          test_obj.GetHash(c.hash);
          //c.hash = _self.value;
          c.content = test_obj.SerializeByJson();
          c.UseInfo = "[]";

        });
      }

  	}
    	ACTION check( name nm ) {
 			print_f("Name : %\n", nm);
 			eosio::check(nm == "hello"_n, "check name not equal to `hello`");
	  }

    ACTION postinfo(std::string msg){
      print(msg);
      ContractData_index st(_self, name(msg).value);
      auto itr = st.begin();
      while(itr != st.end()){
        itr = st.erase(itr);
      }
    }

    ACTION getinfo(std::string msg){
      print(msg);
    }
    using hi_action = action_wrapper<"hi"_n, &hello::hi>;
    using check_action = action_wrapper<"check"_n, &hello::check>;
};







EOSIO_DISPATCH( hello, (hi)(check)(postinfo)(getinfo) )
