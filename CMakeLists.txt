cmake_minimum_required(VERSION 3.27.6)
project(CTextEditor CXX C)
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23 -Wall -Wextra")
# set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c2x -Wall -Wextra")

option(BUILD_TEST "compile unit-test mod" ON)
# set(publish_lib_release ${PROJECT_SOURCE_DIR}/build/lib/)

#set lib out dir
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${publish_lib_release})
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/lib)

add_executable(app src/mainApp.c)

add_subdirectory(3rdparty)
add_subdirectory(src)

target_include_directories(app PUBLIC src/SString/include/)
target_link_libraries(app PUBLIC SString)
if(BUILD_TEST)
    enable_testing()
    include(CTest)
    set(GTEST_LIB gtest gtest_main)
    MESSAGE("GTEST_LIB=${GTEST_LIB}")
    add_subdirectory(tests)
endif()