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
 * @file svector.h
 * @author KSJ
 * @date 2023-10-24
 * @version 0.0.1
 * @brief 已废弃。动态数组模板类,限于c语言，调用模板得先使用SVector_IMPL(T) ,
 *   才能继续使用SVector(T), 对于非平凡类型，必须有 new##T(size_t size) 方法才可使用
 * @bug none found
 * @todo none
 * @warning 已废弃
*/
#include<stdlib.h>
#include<string.h>
#include<sstring.h>
#include<base.h>
#ifndef SVECTOR_H_
#define SVECTOR_H_
#define SVectorChunkSize 5000
/**
 * @brief: 动态数组
*/
#define SVector(T) SVector$_##T##_$
#define SVector_STRUCT_IMPL(T) typedef struct {\
    size_t size;\
    char* data;\
    size_t bufSize;\
} SVector(T);
// 计算所需实际大小

// 分配空间
#define SVectorMalloc(T) SVectorMalloc$_##T##_$
#define SVectorMalloc_IML(T) __declspec(dllexport) void SVectorMalloc(T)(SVector(T)* x, size_t size) {\
    x->bufSize = (size/SVectorChunkSize + 1)*SVectorChunkSize;\
    char* tmp = (char*)calloc(x->bufSize, sizeof(T));\
    for (size_t i = 0; i < x->size; i++) tmp[i] = x->data[i];\
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
// free space
#define freeSVector(T) freeSVector$_##T##_$
#define freeSVector_IMPL(T) void freeSVector(T)(SVector(T) *h){\
    free(h->data);\
    free(h);\
}
// 返回所在位置的指针, 分配空间失败则返回 NULL
#define SVectorAt(T) SVectorAt$_##T##_$
#define SVectorAt_IMPL(T) __declspec(dllexport) T* SVectorAt(T)(SVector(T)* x, size_t pos) {\
    if (pos > x->bufSize) {\
        PrintErr("WARNING", "out of range.");\
        size_t bufSize = (pos/SVectorChunkSize + 1)*SVectorChunkSize;\
        if (NULL == realloc(x, bufSize*sizeof(T))) {\
            PrintErr("ERROR","out of memory.");\
            return (T*)NULL;\
        }\
        x->bufSize = bufSize;\
    }\
    return (T*)(x->data+pos*(sizeof(T)/sizeof(char)));\
}
// insert value in pos
#define SVectorInsert(T) SVectorInsert$_##T##_$
#define SVectorInsert_IMPL(T) void SVectorInsert(T)(SVector(T)* h, T val, size_t pos){\
    T* tmp = SVectorAt(T)(h, pos);\
    *tmp = val;\
}
// append value in vector
#define SVectorAppend(T) SVectorAppend$_##T##_$
#define SVectorAppend_IMPL(T) void SVectorAppend(T)(SVector(T)* h, T val) {\
    SVectorInsert(T)(h, val, h->size+1);\
}


// all import
#define SVector_IMPL(T) SVector_STRUCT_IMPL(T) SVectorMalloc_IML(T) \
        SVectorAt_IMPL(T) SVectorInit_IMPL(T) newSVector_IMPL(T)\
        freeSVector_IMPL(T) SVectorInsert_IMPL(T) SVectorAppend_IMPL(T)
// import vector<size_t>
#ifdef __cplusplus
extern "C" {
#endif
    SIMPLE_TYPE_IMPL(SVector_IMPL);
    SVector_IMPL(SString);
#ifdef __cplusplus
}
#endif

// SVector_IMPL(char);

#endif  // SVECTOR_H_
