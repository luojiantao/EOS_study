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

CONTRACT hello : public contract {
   public:
  	using contract::contract;
    void init(){}
   	ACTION hi( name nm ) {
  		print_f("Name : %\n", nm);
 			auto test_obj = Mediation::CContract();
      testtable_t ll(_self, _self.value);
  	}
    	ACTION check( name nm ) {
 			print_f("Name : %\n", nm);
 			eosio::check(nm == "hello"_n, "check name not equal to `hello`");
	  }

    ACTION post_info(std::string msg){
      print(msg);
    }

    ACTION get_info(std::string msg){
      print(msg);
    }
    TABLE test_table {
      uint64_t owner;
      uint64_t primary_key() const { return owner; }
    }；
    TABLE ContractData {
      uint64_t creator;
      uint64_t hash;// sha256(creator + content)
      string content;
      string UseInfo;///存储所有合约状态的索引

      uint64_t primary_key() const { return hash; }

      uint64_t get_creator() const {return creator; }

      //序列化
      EOSLIB_SERIALIZE(ContractData, (creator)(hash)(content)(UseInfo));
    };

    struct ContractState {
        uint64_t Sponsor;
        uint64_t hash;// sha256(Sponsor + ContractData.hash + describe)
        string describe;
        string State;
        
        uint64_t primary_key() const { return hash; }
       
        uint64_t get_sponsor() const {return Sponsor; }
     
        //序列化
        EOSLIB_SERIALIZE(ContractData, (Sponsor)(hash)(describe)(State));
    };

    typedef eosio::multi_index< "testtab"_n, test_table > testtable_t;
    typedef eosio::multi_index< "contractdata"_n, ContractData,
            indexed_by< "creator"_n, const_mem_fun<ContractData, uint64_t, &ContractData::get_creator > >
            > ContractData_index;
    typedef eosio::multi_index< "contractstate"_n, ContractState,
            indexed_by<N(Sponsor), const_mem_fun<ContractState, uint64_t, &ContractState::get_sponsor>>
            > ContractState_index;

    using hi_action = action_wrapper<"hi"_n, &hello::hi>;
    using check_action = action_wrapper<"check"_n, &hello::check>;
};







EOSIO_DISPATCH( hello, (hi)(check)(post_info)(get_info) )