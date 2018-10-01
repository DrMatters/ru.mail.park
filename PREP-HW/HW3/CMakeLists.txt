cmake_minimum_required(VERSION 3.0)
project(PREP-HW3)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -Weverything -g -O0")

elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -g -O0 -lm")

endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set(DynList_SOURCEFILES DynamicList.c DynamicList.h)
add_library(DynList ${DynList_SOURCEFILES})
add_library(DynListSHARED SHARED ${DynList_SOURCEFILES})

set(SOURCE_FILES main.c)
add_executable(PREP-HW3 ${SOURCE_FILES})

target_link_libraries(PREP-HW3 DynList)