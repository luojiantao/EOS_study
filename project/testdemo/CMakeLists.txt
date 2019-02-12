project(just_test)
  
set(EOSIO_WASM_OLD_BEHAVIOR "Off")
find_package(eosio.cdt)
#1. 合约名字 2.生成文件名字 3.源文件
SET(SRC_FILE
        just_test.cpp
        ${CMAKE_SOURCE_DIR}/../src/Contract.cpp
        ${CMAKE_SOURCE_DIR}/../src/base_64.cpp)
add_contract( hello just_test ${SRC_FILE} )
target_include_directories( just_test PUBLIC ${CMAKE_SOURCE_DIR}/../include ${CMAKE_SOURCE_DIR})
#target_ricardian_directory( just_test ${CMAKE_SOURCE_DIR}/../ricardian )

#生成ABI为你教案
SET(ABI_FILE just_test1.abi)
SET(ABI_SRC_FILE ${CMAKE_SOURCE_DIR}/just_test.cpp)
SET(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/../include)
SET(CONTRACT_NAME ContractInterface)
add_custom_command(OUTPUT ${ABI_FILE} 
COMMAND echo "Generating ${ABI_FILE}..." 
COMMAND rm ${CMAKE_CURRENT_BINARY_DIR}/${ABI_FILE} -f
COMMAND eosio-abigen ${ABI_SRC_FILE} --contract=${CONTRACT_NAME} --output=${ABI_FILE} --extra-arg-before=-I${INCLUDE_DIR}
COMMENT "eosio-abigen")

add_custom_target(Test1 ALL DEPENDS ${ABI_FILE})

#configure_file("${ABI_FILE}" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)

