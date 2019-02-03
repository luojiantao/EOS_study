/*#include <eosiolib/eosio.hpp>
#include "Contract.hpp"
using namespace eosio;

class hello : public eosio::contract {
  public:
      using contract::contract;

      /// @abi action 
      void hi( account_name user ) {
         print( "Hello, ", name{user} );
         auto test_obj = Mediation::CContract();
      }
};

EOSIO_ABI( hello, (hi) )
*/

#include <eosiolib/eosio.hpp>
#include "Contract.hpp"

using namespace eosio;

CONTRACT hello : public contract {
   public:
    	using contract::contract;

     	ACTION hi( name nm ) {
    		print_f("Name : %\n", nm);
   			auto test_obj = Mediation::CContract();
	  	}
      	ACTION check( name nm ) {
   			print_f("Name : %\n", nm);
   			eosio::check(nm == "hello"_n, "check name not equal to `hello`");
		}

      using hi_action = action_wrapper<"hi"_n, &hello::hi>;
      using check_action = action_wrapper<"check"_n, &hello::check>;
};





EOSIO_DISPATCH( hello, (hi)(check) )