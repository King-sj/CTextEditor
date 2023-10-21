cmake_minimum_required(VERSION 3.20)

add_library(SString SHARED)
target_include_directories(SString PUBLIC ../include/)
target_sources(SString PUBLIC sstring.c ../include/sstring.h)

add_library(SVector SHARED)
target_include_directories(SVector PUBLIC ../include/)
target_sources(SVector PUBLIC svector.c ../include/svector.h
    ../include/base.h
)