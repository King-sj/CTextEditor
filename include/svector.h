/* ==================================================================
* Copyright (c) 2023-10-21.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*
* 1. Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright
* notice, this list of conditions and the following disclaimer in the
* documentation and/or other materials provided with the
* distribution.
* 3. All advertising materials mentioning features or use of this software
* must display the following acknowledgement:
* This product includes software developed by the SJ Group. and
* its contributors.
* 4. Neither the name of the Group nor the names of its contributors may
* be used to endorse or promote products derived from this software
* without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY SJ,GROUP AND CONTRIBUTORS
* ===================================================================
* Author: KSJ.
*/
/**
 * @brief : 动态数组模板类,限于c语言，调用模板得先使用SVector_IMPL(T) ,
 *      才能继续使用SVector(T), 对于非平凡类型，必须有 new##T(size_t size) 方法才可使用
*/
#include<stdlib.h>
#include<string.h>
#include<sstring.h>
#include<base.h>
#ifndef SVECTOR_H_
#define SVECTOR_H_
#define SVectorChunkSize 5000
// 定义vector
#define SVector(T) SVector$_##T##_$
#define SVector_STRUCT_IMPL(T) typedef struct {\
    size_t size;\
    char* data;\
    size_t bufSize;\
} SVector(T);
// 分配空间
#define SVectorMalloc(T) SVectorMalloc$_##T##_$
#define SVectorMalloc_IML(T) __declspec(dllexport) void SVectorMalloc(T)(SVector(T)* x, size_t size) {\
    x->bufSize = (size/SVectorChunkSize + 1)*SVectorChunkSize;\
    char* tmp = (char*)malloc(sizeof(T)*x->bufSize*(sizeof(T)/sizeof(char)));\
    for (size_t i = 0; i < x->size; i++) tmp[i] = x->data[i];\
    for (size_t i = x->size; i < size; i++) tmp[i] = 0;\
    free(x->data);\
    x->data = tmp;\
    x->size = size;\
}
// 初始化
#define SVectorInit(T) SVectorInit$_##T##_$
#define SVectorInit_IMPL(T) __declspec(dllexport) void SVectorInit(T)(SVector(T)* x, size_t size) {\
    x->size = 0;\
    x->data = (char*)NULL;\
    SVectorMalloc(T)(x, size);\
}
// new vector
#define newSVector(T) newSVector$_##T##_$
#define newSVector_IMPL(T) __declspec(dllexport) SVector(T)* newSVector(T)(size_t size) {\
    SVector(T)* tmp = (SVector(T)*)malloc(sizeof(SVector(T)));\
    SVectorInit(T)(tmp, size);\
    return tmp;\
}
// #define
// 返回所在位置的指针
#define SVectorAt(T) SVectorAt$_##T##_$
#define SVectorAt_IMPL(T) __declspec(dllexport) T* SVectorAt(T)(SVector(T)* x, size_t pos) {\
    if (pos > x->bufSize) {\
        SVectorMalloc(T)(x, pos+SVectorChunkSize);\
    }\
    return (T*)(x->data+pos*(sizeof(T)/sizeof(char)));\
}
// all import
#define SVector_IMPL(T) SVector_STRUCT_IMPL(T) SVectorMalloc_IML(T) \
        SVectorAt_IMPL(T) SVectorInit_IMPL(T) newSVector_IMPL(T)\
// import vector<size_t>
#ifdef __cplusplus
extern "C" {
#endif
    SVector_IMPL(int);
    SVector_IMPL(size_t);
    SVector_IMPL(double);
    SVector_IMPL(float);
    SVector_IMPL(char);
    SVector_IMPL(intp);
    SVector_IMPL(charp);
    SVector_IMPL(SString);
#ifdef __cplusplus
}
#endif

// SVector_IMPL(char);

#endif  // SVECTOR_H_
