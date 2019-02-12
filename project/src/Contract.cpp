#include "Contract.hpp"

namespace Mediation{
	//CContract::CContract(){}

	CContract::~CContract(){}

    ContractInterface::test(std::string msg){}

}

EOSIO_DISPATCH( Mediation::ContractInterface, (test) )