#pragma once
#include <eosiolib/eosio.hpp>
#include "eosiolib/types.h"
#include "base_64.h"
#include "json.hpp"
using namespace eosio;
using json = nlohmann::json;
using ::memcpy;
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
namespace Mediation{
	using CheckNum = std::string;
	using Msg = std::string;
	using account_name = eosio::name;
	CONTRACT CContract{
		//friend Creator;

		struct ParticipantsState{
	        std::string name;
	        std::string sign;
	        std::string describe;
	        CheckNum check_num;
	        unsigned int weigth;
	        unsigned int index;//后续考虑需不要，删除
        };
	    enum ContractState{
	    	TOBETAKE = 0,
	        TAKED,
	        CONSENSUS_SUCCESS,
	        CONSENSUS_UNSUCCESS,
	        UNCONSENSUS,
	    };
	    TABLE ContractData {
		    uint64_t creator;
		    capi_checksum256 hash;// sha256(creator + content)
		    //checksum256 hash;
		    string content;
		    string UseInfo;///存储所有合约状态的索引

		    uint64_t primary_key() const { return *((uint64_t*)&hash); }

		    uint64_t get_creator() const {return creator; }
		    checksum256 by_hash() const { return capi_checksum256_to_checksum256(hash); }

		    //序列化
		    //EOSLIB_SERIALIZE(ContractData, (creator)(hash)(content)(UseInfo));
	    };

		TABLE ContractState {
	        uint64_t Sponsor;
	        capi_checksum256 contract_hash;
	        capi_checksum256 hash;// sha256(Sponsor + ContractData.hash + describe)
	        string describe;
	        string State;
	      /*
	      {
	        "creator": {
	          id: unit_64,
	          state: int,
	          msg:""
	        },
	        "Sponsor":[{
	          id：，
	          state:,
	          msg:"",
	        }],
	        "Performer":[{
	          id：，
	          state:,
	          msg:"",
	        }]
	      }
	      */
	      
	        uint64_t primary_key() const { return *((uint64_t*)&hash); }
	        checksum256 by_hash() const { return capi_checksum256_to_checksum256(hash); }
	     
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
	            indexed_by<"sponsor"_n, const_mem_fun<ContractState, uint64_t, &ContractState::get_sponsor>>,
	            indexed_by< "hash"_n, const_mem_fun<ContractState, checksum256, &ContractState::by_hash > >
	            > ContractState_index;
    public:
    	ACTION test(std::string msg){

    	}
    	ACTION cleardata(std::string msg){
    		print(msg);
	        ContractData_index st(_self, name(msg).value);
	        auto itr = st.begin();
	        while(itr != st.end()){
	            itr = st.erase(itr);
            }
    	}
    	//参与者分为三种角色：合约创建者，合约发起者，合约参与者
    	template<typename T>
    	T GetParticipants(account_name n);

    	//test
    	CContract():m_storage(name("luo"), name("luo").value)
    	{}

    	/*CContract(account_name create, std::string context = std::string()):
        m_creater(create),m_context(context),m_storage(name("luo"), name("luo").value)
        {
            //capi_checksum256 calc_hash;
            std::string has_head =  name{m_creater}.to_string() + m_context;
            sha256( has_head.c_str(), has_head.length(), &m_hash );

            //print_f("Name : % %\n", m_hash , has_head.c_str());
        }*/
    	void SetContract(account_name create, std::string context ){
    		std::string hash =  name{create}.to_string() + context;	
    		capi_checksum256 calc_hash;
    		sha256( hash.c_str(), hash.length(), &m_hash );

    		auto creator_index = m_storage.get_index<name("hash")>();

		    auto itr = creator_index.find(capi_checksum256_to_checksum256(hash));
		      //auto itr = creator_index.find(_self.value);
		    if (itr != creator_index.end()){
		        print("***exit***", _self.value);
		    //    print(itr->content);
		    }else{
		        print("***insert***");
		        m_storage.emplace(name("luo"), [&](auto& c){
		        c.creator = name("luo").value;

		        td::string hash =  name{create}.to_string() + context;
		        sha256( hash.c_str(), hash.length(), &(c.hash) );
		        //test_obj.GetHash(c.hash);
		          //c.hash = _self.value;
		        c.content = context;
		        c.UseInfo = "[test]";

		        });
		    }
    	}

        std::string SerializeByJson(){
        	/*
				{
					"context"： m_context,
					"hash" : m_hash,
					"max_member" : m_max_member,
					"creater" : m_creater,
					"ParticipantsStateHash":[""],
				}
        	*/
        	json j;
        	j["context"] = m_context;
        	Base64 base;
        	std::string normal,encoded;
        	const unsigned char* ttt = (const unsigned char*)(&m_hash);
        	std::string hash = base.Encode(ttt,sizeof(m_hash));
        	j["hash"] = hash;
        	j["max_member"] = m_max_member;
        	j["creater"] = (uint64_t) m_creater.value;
        	j["ParticipantsState_Hash"] = {"1", "2", "3"};
        	return j.dump();
        }
        void GetHash(capi_checksum256& hash){
        	memcpy(&hash, &m_hash, sizeof(m_hash));
        	//return m_hash;
        }
    	~CContract();
	private:
		ContractState StateCalculate();
    	//void Storage();
    	ContractData_index m_storage;
        Msg m_context;
        account_name m_creater;
	    unsigned short m_max_member = 1;
	    capi_checksum256 m_hash;//hash(m_creater + m_context)
	    //std::string m_next_hash;
	    int m_contract_value = 0;
	    int m_sign_value = 0;

        std::vector<ParticipantsState*> m_member_vector;
	};
}

EOSIO_DISPATCH( CContract, (test) )