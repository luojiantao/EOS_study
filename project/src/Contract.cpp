#include "Contract.hpp"

namespace Mediation{
	//CContract::CContract(){}

	CContract::~CContract(){}

    //ContractInterface::test(std::string msg){}
	ACTION ContractInterface::test(std::string msg){
    	auto aa = Mediation::CContract();
    }

	ACTION ContractInterface::cleardata(std::string msg){
	print(msg);
    ContractData_index st(_self, name(msg).value);
    auto itr = st.begin();
    while(itr != st.end()){
        itr = st.erase(itr);
    }

}

EOSIO_DISPATCH( Mediation::ContractInterface, (test)(cleardata) )