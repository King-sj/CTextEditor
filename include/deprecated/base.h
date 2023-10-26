/**
* @copyright ==================================================================
*  Copyright (c) 2023-10-24.
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*  1. Redistributions of source code must retain the above copyright
*  notice, this list of conditions and the following disclaimer.
*  2. Redistributions in binary form must reproduce the above copyright
*  notice, this list of conditions and the following disclaimer in the
*  documentation and/or other materials provided with the
*  distribution.
*  3. All advertising materials mentioning features or use of this software
*  must display the following acknowledgement:
*  This product includes software developed by the SJ Group. and
*  its contributors.
*  4. Neither the name of the Group nor the names of its contributors may
*  be used to endorse or promote products derived from this software
*  without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY SongJian, GROUP AND CONTRIBUTORS
*  ===================================================================
* @file base.h
* @author KSJ
* @date 2023-10-24
* @version 0.0.1
* @brief 公共宏、函数、常量
* @bug none found
* @todo none
* @warning some shouldn't do
*/
#ifndef __cplusplus
    #include<string.h>
    #include<stdlib.h>
    #include<inttypes.h>
    #include<stdint.h>
    #include<stdio.h>
    #include<time.h>
    #include<stdbool.h>
#endif
#include<concepts>
#ifndef BASE_H_
#define BASE_H_
// #ifdef __cplusplus
// extern "C" {
// #endif
#define Macro2Str(X) #X
typedef long long ll;
typedef unsigned long long ull;
typedef int* intp;
typedef char* charp;
#define SIMPLE_TYPE_IMPL(CLASS_IMPL)\
    CLASS_IMPL(int);\
    CLASS_IMPL(double);\
    CLASS_IMPL(float);\
    CLASS_IMPL(char);\
    CLASS_IMPL(intp);\
    CLASS_IMPL(charp);
#define PrintErr(ty, Msg) \
    time_t curtime;\
    time(&curtime);\
    fprintf(stderr, "(%s)[%s] [%s:%llu] :\n\t %s\n\n", ty, ctime(&curtime), __FILE__, __LINE__, Msg);
// 判断 x 是否在 [l, r)
#define isInRange(T) isInRange$_##T##_$
#define isInRange_IMPL(T) bool isInRange(T)(T x, T l, T r) {\
    return l <= x && x < r;\
}
SIMPLE_TYPE_IMPL(isInRange_IMPL);

template<typename T>
concept ExistDefaultConstruction = std::is_pointer<T>::value || requires(T x) {
    x = T();
};

// #ifdef __cplusplus
// extern }
// #endif
#endif  // BASE_H_
