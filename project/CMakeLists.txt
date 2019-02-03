include(ExternalProject)
# if no cdt root is given use default path
if(EOSIO_CDT_ROOT STREQUAL "" OR NOT EOSIO_CDT_ROOT)
   find_package(eosio.cdt)
endif()
SET(SRC_DIR
        ${CMAKE_SOURCE_DIR}/testdemo)

ExternalProject_Add(
   hello_project
   SOURCE_DIR ${SRC_DIR}
   BINARY_DIR ${CMAKE_BINARY_DIR}/project
   CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${EOSIO_CDT_ROOT}/lib/cmake/eosio.cdt/EosioWasmToolchain.cmake
   UPDATE_COMMAND ""
   PATCH_COMMAND ""
   TEST_COMMAND ""
   INSTALL_COMMAND ""
   BUILD_ALWAYS 1
)

#ExternalProject_Add(
#   hello_tests_project
#   SOURCE_DIR ${CMAKE_SOURCE_DIR}/tests
#   BINARY_DIR ${CMAKE_BINARY_DIR}/tests
#   CMAKE_ARGS -DCMAKE_TOOLCHAIN_FILE=${EOSIO_CDT_ROOT}/lib/cmake/eosio.cdt/EosioWasmToolchain.cmake
#   UPDATE_COMMAND ""
#   PATCH_COMMAND ""
#   TEST_COMMAND ""
#   INSTALL_COMMAND ""
#   BUILD_ALWAYS 1
#)