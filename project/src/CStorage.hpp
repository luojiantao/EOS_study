#pragma once
#include <eosiolib/eosio.hpp>
#include<string>
#include<stdlib.h>
use namespace std;
namespace ContractStorage{
//Scope
//合约内容存储
//@abi table ContractData i64
struct ContractData {
    uint64_t creator;
    uint64_t hash;// sha256(creator + content)
    string content;
    string UseInfo;//存储所有合约状态的索引

    uint64_t primary_key() const { return hash; }

    uint64_t get_creator() const {return creator; }
 
    //序列化
    EOSLIB_SERIALIZE(ContractData, (creator)(hash)(content)(UseInfo));
};

typedef eosio::multi_index< N(ContractData), ContractData,
            indexed_by<N(creator), const_mem_fun<ContractData, uint64_t, &ContractData::get_creator>>>
    ContractData_index;
    


//合约状态存储
//@abi table ContractState i64
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

	typedef eosio::multi_index< N(ContractState), ContractState,
            indexed_by<N(Sponsor), const_mem_fun<ContractState, uint64_t, &ContractState::get_sponsor>>>
    ContractData_index;
	
	class CStorage{	
	};
   //Storage();
  // GetContract();
}
