#pragma once
#include <eosiolib/eosio.hpp>
#include "eosiolib/types.h"
#include "base_64.h"
#include "json.hpp"
using namespace eosio;
using json = nlohmann::json;
using ::memcpy;
namespace Mediation{
	using CheckNum = std::string;
	using Msg = std::string;
	using account_name = eosio::name;
	class CContract{
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
    public:
    	//参与者分为三种角色：合约创建者，合约发起者，合约参与者
    	template<typename T>
    	T GetParticipants(account_name n);

    	//test
    	CContract();
    	CContract(account_name create, std::string context = std::string()):
        m_creater(create),m_context(context)
        {
            //capi_checksum256 calc_hash;
            std::string has_head =  name{m_creater}.to_string() + m_context;
            sha256( has_head.c_str(), has_head.length(), &m_hash );

            //print_f("Name : % %\n", m_hash , has_head.c_str());
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
    	void Storage();
    	
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