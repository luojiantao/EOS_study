#include <eosiolib/eosio.hpp>
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