cmake_minimum_required(VERSION 3.0)
project(AlgHW2)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11 -Weverything -g -O0")

elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++11 -g -O0 -lm")

endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(MyString_SOURCE_FILES String.cpp String.hpp)
add_library(MyString ${MyString_SOURCE_FILES})

set(SOURCE_FILES main.cpp)
add_executable(AlgHW2 ${SOURCE_FILES})

target_link_libraries(AlgHW2 MyString)
