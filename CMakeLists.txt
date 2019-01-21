# Set the minimum required version of cmake for a project
cmake_minimum_required(VERSION 3.5)

# Set a name, version, and enable languages for the entire project.
project( ProjectName )

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/libraries/fc/CMakeModules")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")

# Load and run CMake code from a file or module.
include( GNUInstallDirs )
include( SetupTargetMacros )

# Set a normal, cache, or environment variable to a given value
set( CMAKE_CXX_STANDARD 14 )
set( CMAKE_CXX_EXTENSIONS ON )
set( CXX_STANDARD_REQUIRED ON)

set( CLI_CLIENT_EXECUTABLE_NAME cleos )
set( GUI_CLIENT_EXECUTABLE_NAME eosio )
# flag_luo
set(WASM_ROOT "/opt/wasm")
set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

# add defaults for openssl
if ("${OPENSSL_ROOT_DIR}" STREQUAL "")
   if (NOT "$ENV{OPENSSL_ROOT_DIR}" STREQUAL "")
      set(OPENSSL_ROOT_DIR $ENV{OPENSSL_ROOT_DIR})
      set(OPENSSL_INCLUDE_DIR ${OPENSSL_ROOT_DIR}/include)
   elseif (APPLE)
      set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl")
      set(OPENSSL_INCLUDE_DIR "/usr/local/opt/openssl/include")
   elseif(UNIX AND NOT APPLE)
      set(OPENSSL_ROOT_DIR "/usr/include/openssl")
      set(OPENSSL_INCLUDE_DIR "/usr/include/openssl/include")
   else()
      message(FATAL_ERROR "openssl not found and don't know where to look, please specify OPENSSL_ROOT_DIR")
   endif()
endif()

if(UNIX)
  if(APPLE)
    set(whole_archive_flag "-force_load")
    set(no_whole_archive_flag "")
  else()
    set(whole_archive_flag "--whole-archive")
    set(no_whole_archive_flag "--no-whole-archive")
  endif()
else()
  set(whole_archive_flag "--whole-archive")
  set(no_whole_archive_flag "--no-whole-archive")
endif()

SET( Boost_USE_STATIC_LIBS ON CACHE STRING "ON or OFF" )
IF( WIN32 )
  SET(BOOST_ROOT $ENV{BOOST_ROOT})
  set(Boost_USE_MULTITHREADED ON)
  set(BOOST_ALL_DYN_LINK OFF) # force dynamic linking for all libraries
ENDIF(WIN32)
FIND_PACKAGE(Boost 1.66 REQUIRED COMPONENTS
    thread
    date_time
    filesystem
    system
    program_options
    signals
    serialization
    chrono
    unit_test_framework
    context
    locale
    iostreams)

# Add a subdirectory to the build.
add_subdirectory(externals)

include(wasm)

add_subdirectory(libraries)
add_subdirectory(contracts)
