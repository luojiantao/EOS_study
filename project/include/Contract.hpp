#pragma once
#include <eosiolib/eosio.hpp>
#include "eosiolib/types.h"
#include "base_64.h"
using namespace eosio;
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
            capi_checksum256 calc_hash;
            std::string has_head =  name{m_creater}.to_string() + m_context;
            sha256( has_head.c_str(), m_context.length(), &calc_hash );
            Base64 base;
            std::string normal,encoded;
            const unsigned char* ttt = (const unsigned char*)(&calc_hash);
            m_hash = base.Encode(ttt,sizeof(calc_hash));
            print_f("Name : %  % %\n", m_hash.c_str(), m_hash.length(), has_head.c_str());
        }

    	~CContract();
	private:
		ContractState StateCalculate();
    	std::string Serialize();
    	void Storage();
    	
        Msg m_context;
        account_name m_creater;
	    unsigned short m_max_member = 1;
	    std::string m_hash;//hash(m_creater + m_context)
	    std::string m_next_hash;
	    int m_contract_value = 0;
	    int m_sign_value = 0;

        std::vector<ParticipantsState*> m_member_vector;
	};
}