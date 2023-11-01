cmake_minimum_required(VERSION 3.27.6)
project(CTextEditor LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 23)
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++23 -Wall -Wextra")
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak -fsanitize=addres")
# set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c2x -Wall -Wextra")

add_compile_definitions(RESOURCE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resource/")


option(BUILD_TEST "compile unit-test mod" ON)
# set(publish_lib_release ${PROJECT_SOURCE_DIR}/build/lib/)

#set lib out dir
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ${publish_lib_release})
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/bin)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/build/lib)

add_subdirectory(3rdparty)
add_subdirectory(src)

add_executable(app src/mainApp.cpp src/KString.cpp src/TextLine.cpp
    src/TextEdit.cpp src/menu.cpp)
target_include_directories(app PUBLIC include/ 3rdparty/cxxopts/include)
target_compile_definitions(app PRIVATE RESOURCE_PATH)

# target_sources(./include)
if(BUILD_TEST)
    enable_testing()
    include(CTest)
    set(GTEST_LIB gtest gtest_main)
    MESSAGE("GTEST_LIB=${GTEST_LIB}")
    add_subdirectory(tests)
endif()


install(TARGETS
    app
    RUNTIME # Following options apply to runtime artifacts.
        COMPONENT Runtime
    LIBRARY  # Following options apply to library artifacts.
        COMPONENT Runtime
        NAMELINK_COMPONENT Development
    ARCHIVE           # Following options apply to archive artifacts.
        COMPONENT Development
        DESTINATION lib/static
    FILE_SET HEADERS  # Following options apply to file set HEADERS.
        COMPONENT Development
)
add_executable(tmp tmp/tmp.cpp)
target_include_directories(tmp PUBLIC include/ 3rdparty/cxxopts/include)