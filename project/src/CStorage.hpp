#pragma once
#include "luo.hpp"
namespace ContractStorage{

//合约内容存储
//@abi table ContractData i64
struct ContractData {
    uint64_t creator;
    uint64_t hash;// sha256(account + content)
    string content;
    string UseInfo;//存储所有合约状态的索引
    //定义address表的主键
    uint64_t primary_key() const { return creator; }
    //定义extractor，二级索引是phone
    uint64_t get_hash() const {return hash; }
 
    //序列化
    EOSLIB_SERIALIZE(ContractData, (creator)(hash)(content));
};
//合约状态存储
//@abi table ContractState i64
struct ContractState {
    uint64_t Sponsor;
    uint64_t hash;// sha256(Sponsor + ContractData.hash + describe)
    string describe;
    string State;
    
    //定义address表的主键
    uint64_t primary_key() const { return hash; }
    //定义extractor，二级索引是phone
    uint64_t get_Sponsor() const {return Sponsor; }
 
    //序列化
    EOSLIB_SERIALIZE(ContractData, (Sponsor)(hash)(describe)(State));
};

	class CStorage{
		
	};
   //Storage();
  // GetContract();
}