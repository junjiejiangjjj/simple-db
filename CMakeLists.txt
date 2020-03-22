cmake_minimum_required (VERSION 3.5)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

SET(CMAKE_C_COMPILER "/usr/bin/gcc")
SET(CMAKE_CXX_COMPILER "/usr/bin/g++")

# 项目信息
project (Simple-DB VERSION 0.0.1 LANGUAGES C CXX)

INCLUDE_DIRECTORIES(
  ${PROJECT_SOURCE_DIR}/

  /usr/local/include
  /usr/include
)

LINK_DIRECTORIES(
  ${PROJECT_BINARY_DIR}/lib
  /usr/local/lib
  /usr/lib
)

if(DEBUG_FLAG)
    SET(DEBUG_FLAG "-g")
    SET(BUILD_CONFIGURATION_ "debug")
else()
    SET(DEBUG_FLAG "-DNDEBUG")
    SET(BUILD_CONFIGURATION "release")
endif()

# list(APPEND flags "-fPIC" "-Wall" "-Wextra" "-Wpedantic")

set(CMAKE_CXX_FLAGS "-g -std=c++14 -pthread -fPIC -W -Wall")

find_program(MEMORYCHECK_COMMAND NAMES valgrind)
set(MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full")

include(CTest)

enable_testing()

add_subdirectory(simple_db)
