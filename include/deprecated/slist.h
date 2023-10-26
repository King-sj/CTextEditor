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
* @file slist.h
* @author KSJ
* @date 2023-10-24
* @version 0.0.1
* @brief 已废弃。使用c宏实现的 list<T>
* @bug none found
* @todo none
* @warning 已废弃
*/
#include<base.h>
#include<sstring.h>
#ifndef SLIST_H_
#define SLIST_H_
#define SListChunkSize 5000
/**
 * @brief: 链表类
 * @param:
 *      nxt: 下一块的地址
 *      pre: 上一块的地址
 *      data: 当前块的所有数据，大小为sizeof(T)
 *
*/

#define SList(T) SList$_##T##_$
#define SList_CLASS_IMPL(T) typedef struct {\
    void* nxt;\
    void* pre;\
    char* data;\
} SList(T);
// malloc space
#define SListMalloc(T) SListMalloc$_##T##_$
#define SListMalloc_IMPL(T) void SListMalloc(T)(SList(T) *h) {\
    h->data = (char*)calloc(1, sizeof(T));\
}
// init , should sure that h is valid
#define SListInit(T) SListInit$_##T##_$
#define SListInit_IMPL(T) void SListInit(T)(SList(T)*h) {\
    SListMalloc(T)(h);\
    h->nxt = NULL;\
    h->pre = NULL;\
}
// new a SList<T>
#define newSList(T) newSList$_##T##_$
#define newSList_IMPL(T) SList(T)* newSList(T)() {\
    SList(T)* h = (SList(T)*)malloc(sizeof(SList(T)));\
    SListInit(T)(h);\
    return h;\
}
// current val
#define SListVal(T) SListVal$_##T##_$
#define SListVal_IMPL(T) T* SListVal(T)(SList(T)* h) {\
    return (T*)h->data;\
}
// nxt data in SList<T>
#define SListNext(T) SListNext$_##T##_$
#define SListNext_IMPL(T) T* SListNext(T)(SList(T)* h) {\
    if (NULL == h->nxt) {\
        PrintErr("ERROR", "nxt is invalid");\
        return NULL;\
    }\
    h = (SList(T)*)h->nxt;\
    return (T*)h->data;\
}
// pre data in SList<T>
#define SListPre(T) SListPre$_##T##_$
#define SListPre_IMPL(T) T* SListPre(T)(SList(T)* h) {\
    if (NULL == h->pre) {\
        PrintErr("ERROR", "pre is invalid");\
        return NULL;\
    }\
    h = (SList(T)*)h->pre;\
    return (T*)h->data;\
}
// insert back
#define SListInsertBack(T) SListInsertBack$_##T##_$
#define SListInsertBack_IMPL(T) void SListInsertBack(T)(SList(T)* h, T val) {\
    SList(T)* tmp = newSList(T)();\
    *(SListVal(T)(h)) = val;\
    tmp->nxt = h->nxt;\
    tmp->pre = (void*)h;\
    if (NULL != h->nxt) {\
        SList(T)* p = (SList(T)*)(h->nxt);\
        p->pre = (void*)tmp;\
    }\
    h->nxt = (void*)tmp;\
}
// insert pre
#define SListInsertPre(T) SListInsertPre$_##T##_$
#define SListInsertPre_IMPL(T) void SListInsertPre(T)(SList(T)* h, T val) {\
    if (NULL == h->pre) {\
        SList(T)* tmp = newSList(T)();\
        tmp->nxt = (void*)h;\
        h->pre = (void*)tmp;\
        *(SListVal(T)(tmp)) = val;\
        return;\
    }\
    SListInsertBack(T)((SList(T)*)h->pre, val);\
}
// point move offset
#define SListMovP(T) SListMovP$_##T##_$
#define SListMovP_IMPL(T) SList(T)* SListMovP(T)(SList(T)** h, int offset) {\
    while (NULL != *h) {\
        if (offset == 0) return *h;\
        if (offset > 0 ) *h = (SList(T)*)(*h)->nxt, --offset;\
        if (offset < 0 ) *h = (SList(T)*)(*h)->pre, ++offset;\
    }\
    PrintErr("ERROR", "aim pos is null, now is in head(tail)");\
    return NULL;\
}
// import all function
#define SList_IMPL(T) SList_CLASS_IMPL(T) SListMalloc_IMPL(T) SListInit_IMPL(T)\
        newSList_IMPL(T) SListVal_IMPL(T) SListNext_IMPL(T) SListPre_IMPL(T)\
        SListInsertBack_IMPL(T) SListInsertPre_IMPL(T) SListMovP_IMPL(T)
#ifdef __cplusplus
extern "C"{
#endif
    SIMPLE_TYPE_IMPL(SList_IMPL);
#ifdef __cplusplus
}
#endif

#endif  // SLIST_H_
