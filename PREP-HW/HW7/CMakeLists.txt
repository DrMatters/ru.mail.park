cmake_minimum_required(VERSION 3.0)
project(PREP-HW7)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++14 -Weverything -g -O0")

elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++14 -g -O0 -lm")

endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(MyLib_SOURCEFILES String.cpp String.hpp Vector.hpp)
add_library(MyLib ${MyLib_SOURCEFILES})

set(SOURCE_FILES main.cpp)
add_executable(PREP-HW7 ${SOURCE_FILES})

target_link_libraries(PREP-HW7 MyLib)
