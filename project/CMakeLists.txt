#https://github.com/nlohmann/json.git json单文件版本
#file(GLOB ABI_FILES "test.abi")
#configure_file("${ABI_FILES}" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
#include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
#link_directories("${CMAKE_CURRENT_SOURCE_DIR}/lib")
set(SRC_FILE 
	${CMAKE_CURRENT_SOURCE_DIR}/src/Contract.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/testdemo/just_test.cpp)
set(INCLUDE_FILE 
	${CMAKE_CURRENT_SOURCE_DIR}/include)


#add_executable(testdemo testdemo/jsoncpp_test.cpp)
#add_wast_executable(TARGET hello
  INCLUDE_FOLDERS "${STANDARD_INCLUDE_FOLDERS}" "${INCLUDE_FILE}"
  SOURCE_FILES "${SRC_FILE}"
  LIBRARIES libc libc++ eosiolib
  DESTINATION_FOLDER ${CMAKE_CURRENT_BINARY_DIR}
)
#target_link_libraries(testdemo libjsoncpp.a)
