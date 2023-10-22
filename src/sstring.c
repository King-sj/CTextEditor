#include<sstring.h>
#include<stdio.h>
#include<stdlib.h>
#include<base.h>
#define ChunkSize 50  // 单次申请的字符数组的大小
#ifdef __cplusplus
extern "C" {
#endif
// 申请不小于bufSize的空间, 该方法会清空 h.data
void mallocSStringBuf(SString* h, size_t bufSize);
// 初始化字符串
void initSString(SString* h, size_t size);

SString* newSString(size_t size) {
    SString* tmp = (SString*)malloc(sizeof(SString));
    initSString(tmp, size);
    return tmp;
}
// 初始化字符串
void initSString(SString* h, size_t size) {
    h->data = NULL;  // note:
    mallocSStringBuf(h, size);
    h->data[0] = 0;
    h->length = 0;
}
// 释放字符串
void freeInitSString(SString* h) {
    free(h->data);
    free(h);
}
// 复制字符串
void copySString(SString* src, SString* dest) {
    fillSString(dest, src->data, src->length);
}

void fillSString(SString* dest, char* data, size_t maxSize) {
    maxSize++;  // 多留一个存 \0
    if (dest->bufferSize < maxSize)mallocSStringBuf(dest, maxSize);
    size_t i;
    dest->length = 0;
    for (i = 0; data[i] && i < dest->bufferSize; i++)
        dest->data[i] = data[i], dest->length++;
    dest->data[i] = 0;
}

char* getSStringData(SString* h) {
    return h->data;
}

size_t getSStringLength(SString* h) {
    return h->length;
}

void mallocSStringBuf(SString* h, size_t bufSize) {
    size_t cnt = bufSize / ChunkSize;
    free(h->data);
    h->bufferSize = (cnt+1)*ChunkSize;
    h->data = (char*)malloc(sizeof(char) * h->bufferSize );
}

__declspec(dllexport) bool isEqualSString(SString* l, SString* r) {
    return isEqualChars(l->data, r->data);
}

__declspec(dllexport) bool isEqualSStringChars(SString* l, char* r) {
    return isEqualChars(l->data, r);
}

__declspec(dllexport) bool isEqualChars(char* l, char* r) {
    size_t i;
    for (i = 0; l[i] && r[i] && l[i] == r[i]; i++) {}
    return l[i] == r[i];
}

#ifdef __cplusplus
}
#endif
