#file(GLOB ABI_FILES "test.abi")
#configure_file("${ABI_FILES}" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib")

add_executable(testdemo testdemo/jsoncpp_test.cpp)
#add_wast_executable(TARGET hello
#  INCLUDE_FOLDERS "${STANDARD_INCLUDE_FOLDERS}"
#  LIBRARIES libc libc++ eosiolib
#  DESTINATION_FOLDER ${CMAKE_CURRENT_BINARY_DIR}
#)
target_link_libraries(testdemo libjsoncpp.a)