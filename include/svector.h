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
 *      才能继续使用SVector(T), 对于非平凡类型，必须有 new##T(int size) 方法才可使用
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
    unsigned int size;\
    T* data;\
    unsigned int bufSize;\
} SVector(T);
// 分配空间
#define SVectorMalloc(T) SVectorMalloc$_##T_##$
#define SVectorMalloc_IML(T) void SVectorMalloc(T)(SVector(T)* x, unsigned int size) {\
    x->bufSize = (size/SVectorChunkSize + 1)*SVectorChunkSize;\
    T* tmp = (T*)malloc(sizeof(T)*x->bufSize);\
    for (int i = 0; i < x->size; i++) tmp[i] = x->data[i];\
    for (int i = x->size; i < size; i++) tmp[i] = *newT(T)(0);\
    free(x->data);\
    x->data = tmp;\
    x->size = size;\
}
// 初始化
#define SVectorInit(T) SVectorInit$_##T##_$
#define SVectorInit_IMPL(T) void SVectorInit(T)(SVector(T)* x, unsigned int size) {\
    x->size = 0;\
    x->data = newT(T)(0);\
    SVectorMalloc(T)(x, size);\
}
// new vector
#define newSVector(T) newSVector$_##T##_$
#define newSVector_IMPL(T) SVector(T)* newSVector(T)(unsigned int size) {\
    SVector(T)* tmp;\
    SVectorInit(T)(tmp, size);\
    return tmp;\
}
// #define
// 返回所在位置的指针
#define SVectorAt(T) SVectorAt$_##T_$
#define SVectorAt_IMPL(T) T* SVectorAt(T)(SVector(T)* x, unsigned int pos) {\
    if (pos > x->size) {\
        SVectorMalloc(T)(x, x->size+SVectorChunkSize);\
    }\
    return &x->data[pos];\
}
// all import
#define SVector_IMPL(T) SVector_STRUCT_IMPL(T) SVectorMalloc_IML(T) \
        SVectorAt_IMPL(T) SVectorInit_IMPL(T) newSVector_IMPL(T)\
// import vector<int>
SVector_IMPL(int);
SVector_IMPL(char);
SVector_IMPL(SString);
#endif  // SVECTOR_H_
