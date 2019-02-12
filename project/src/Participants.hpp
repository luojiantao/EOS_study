#pragma once
#include <eosiolib/eosio.hpp>
#include "json.hpp"

using json = nlohmann::json;
//#include "Contract.hpp"
using namespace eosio;
namespace Participants{
	class MemberData{
	public:
		enum MemberType
		{
			Creator =0,
			Sponsor,
			Performer,
			Unkonw
		};
	std::string SerializeByJson(){
        json j;
        j["type"] = (unsigned int)m_type;
        j["state"] = m_state;
        j["msg"] = m_msg;
        j["name"] = m_name;
        return j.dump();
	}
	bool check(){
		return (m_type != MemberType::Unkonw)&&(m_name != 0)&&(m_state != -1)&&(m_msg != "null");
	}
	bool InitFromJson(std::string context){
		json j = json::parse(context);
		m_state = (MemberType)j["type"];
		m_state = j["state"];
		m_name = j["name"];
		m_msg = j["msg"];
		return check();
	}
	protected:
		type m_type = MemberType::Unkonw;
		uint64_t m_name = 0;
		int m_state = -1;
		std::string m_msg = "null";

	};

	class Creator: public BaseMember{
	public:
		Creator(MemberData* data):m_data(data){}
	private:
		MemberData* m_data;
	};

	class Sponsor: public BaseMember{
	public:
		Sponsor(MemberData* data):m_data(data){}
	private:
		MemberData* m_data;
	};

	class Performer: public BaseMember{
	public:
		Performer(MemberData* data):m_data(data){}
	private:
		MemberData* m_data;
	};

}