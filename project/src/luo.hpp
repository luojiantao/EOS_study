#include <eosiolib/eosio.hpp>
#include <string>
#include <stdlib.h>
#include <stdio.h>

using namespace eosio;
namespace ContractStorage{
	class CStorage;
   //Storage();
  // GetContract();
}

//操作内存中合约
//: public eosio::contract
//using contract::contract;
namespace Mediation{
using Msg = std::string;	
	enum CheckNum{
	    UNKONW = 0,
	    CHECK = 1,
	    UNCHECK = 2,
	};
 
    class MediationContract /*final*/{
	friend class CStorage;
        struct MemberState{
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
        MediationContract(Msg body);
    public:
        static MediationContract& CreateContract(Msg context);
	    static void DeleteContract(MediationContract& contract);
	    static MediationContract& FindContract(const std::string hash);

	    ~MediationContract();
	    MediationContract(const MediationContract&) = delete;//拷贝构造函数
	    MediationContract& operator=(const MediationContract&) = delete;//拷贝赋值
	    //*****************合约操作*************************//
        ContractState GetContractState();
	    std::string GetMemberState();
          //甲方
        void FirstSign(account_name si, std::string sign);
	    void FirstCheck(const std::string& check_num, CheckNum num);

	  //乙方
        void OtherSign(account_name si, std::string sign);
	    void OtherCheck(const std::string& check_num, CheckNum num);

        /// @abi action 
        void test( std::string user);
        //void test( account_name user);
    private:
        Msg m_context;
        account_name m_creater;
	    unsigned short m_max_member = 1;
	    std::string m_hash;
	    std::string m_next_hash;
	    int m_contract_value = 0;
	    int m_sign_value = 0;

        std::vector<MemberState*> m_member_vector;

    };
}
//EOSIO_ABI( MediationContract, (hi) )
