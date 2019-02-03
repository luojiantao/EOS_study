project(just_test)
  
set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)
#1. 合约名字 2.生成文件名字 3.源文件
SET(SRC_FILE
        just_test.cpp
        ${CMAKE_SOURCE_DIR}/../src/Contract.cpp)
add_contract( hello just_test ${SRC_FILE} )
target_include_directories( just_test PUBLIC ${CMAKE_SOURCE_DIR}/../include ${CMAKE_SOURCE_DIR})
#target_ricardian_directory( just_test ${CMAKE_SOURCE_DIR}/../ricardian )
