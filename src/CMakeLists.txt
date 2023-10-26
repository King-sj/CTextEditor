cmake_minimum_required(VERSION 3.20)
project(sub)
# set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/build)

option(enable_deprecated_c_lib "是否启用c构建的库" OFF)
if(enable_deprecated_c_lib)
add_library(SString SHARED)
target_include_directories(SString PUBLIC ../include/)
target_sources(SString PUBLIC sstring.c ../include/sstring.h)

add_library(SVector SHARED)
target_include_directories(SVector PUBLIC ../include/)
target_sources(SVector PUBLIC svector.c ../include/svector.h
    ../include/base.h
)

add_library(SList SHARED)
target_include_directories(SVector PUBLIC ../include/)
target_sources(SList PUBLIC slist.c ../include/slist.h
    ../include/base.h
)
endif(enable_deprecated_c_lib)

