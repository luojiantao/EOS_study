#include "Contract.hpp"

namespace Mediation{
	//CContract::CContract(){}

	CContract::~CContract(){}

    //ContractInterface::test(std::string msg){}
	ACTION ContractInterface::test(std::string msg){
    	/*auto Obj = Mediation::CContract();
    	capi_checksum256 calc_hash;
    	Obj.SetContract(name("luo"), "test", calc_hash);
	    Base64 base;
    	std::string normal,encoded;
    	const unsigned char* ttt = (const unsigned char*)(&calc_hash);
    	std::string hash = base.Encode(ttt,sizeof(calc_hash));
    	print("ret:: ", hash);*/
    	//Mediation::SetContract(name("luo"), "test");
    	//Mediation::
		/*action(
            permission_level{ name("luo"), N(active) },
            N(luo), N(setcontract),
            std::make_tuple(from, _self, quantity, std::string(""))
         ).send();*/

		SEND_INLINE_ACTION(*this, setcontract, {name("luo"), N(active)}, {name(luo), "test11"});
    }

	ACTION ContractInterface::cleardata(std::string msg){
		print(msg);
	    ContractData_index st(name("luo"), name(msg).value);
	    auto itr = st.begin();
	    while(itr != st.end()){
	        itr = st.erase(itr);
	    }

	    ContractState_index st0(name("luo"), name("luo").value);
	    auto itr0 = st0.begin();
	    while(itr0 != st0.end()){
	    	itr0 = st0.erase(itr0);
	    }
	}
	ACTION setcontract(name create, std::string msg){
		auto Obj = Mediation::CContract();
		capi_checksum256 calc_hash;//设置合约的hash
		json j = json::parse(msg);
		//string creator = j["data"]["creator"];

		Obj.SetContract(create, msg, calc_hash);
		signed char put[32] = {};
		memcpy(put, calc_hash, 32);
		print("contract hash::", string(put, 32));
	}

}

EOSIO_DISPATCH( Mediation::ContractInterface, (test)(cleardata) )