cmake_minimum_required(VERSION 3.27.6)
project(CTextEditor CXX C)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23 -Wall -Wextra")
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c23 -Wall -Wextra")

option(BUILD_TEST "compile unit-test mod" ON)

add_subdirectory(3rdparty)

if(BUILD_TEST)
    enable_testing()
    include(CTest)
    include_directories()
    set(GTEST_LIB gtest gtest_main)
    MESSAGE("GTEST_LIB=${GTEST_LIB}")
    link_libraries(${GTEST_LIB})
    add_subdirectory(tests)
endif()