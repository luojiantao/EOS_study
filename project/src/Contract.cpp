#include "Contract.hpp"

namespace Mediation{
	//CContract::CContract(){}

	CContract::~CContract(){}

    //ContractInterface::test(std::string msg){}
	ACTION ContractInterface::test(std::string msg){
    	auto Obj = Mediation::CContract();
    	capi_checksum256 calc_hash;
    	Obj.SetContract(name("luo"), "test", calc_hash);
    	print("ret:: ", calc_hash);
    	//Mediation::SetContract(name("luo"), "test");
    	//Mediation::

    }

	ACTION ContractInterface::cleardata(std::string msg){
		print(msg);
	    ContractData_index st(_self, name(msg).value);
	    auto itr = st.begin();
	    while(itr != st.end()){
	        itr = st.erase(itr);
	    }
	}

}

EOSIO_DISPATCH( Mediation::ContractInterface, (test)(cleardata) )