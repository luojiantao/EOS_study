project(just_test)
  
set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)

add_contract( just_test just_test just_test.cpp )
target_include_directories( just_test PUBLIC ${CMAKE_SOURCE_DIR}/../include ${CMAKE_SOURCE_DIR})
#target_ricardian_directory( just_test ${CMAKE_SOURCE_DIR}/../ricardian )
