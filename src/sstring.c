#include<sstring.h>
#include<stdio.h>
#include<stdlib.h>
#define ChunkSize 50  // 单次申请的字符数组的大小
// 申请不小于bufSize的空间, 该方法会清空 h.data
void mallocSStringBuf(SString* h, unsigned int bufSize);
// 初始化字符串
void initSString(SString* h, unsigned int size);


SString* newSString(int size) {
    SString* tmp = (SString*)malloc(sizeof(SString));
    initSString(tmp, size);
    return tmp;
}
// 初始化字符串
void initSString(SString* h, unsigned int size) {
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

void fillSString(SString* dest, char* data, unsigned int maxSize) {
    maxSize++;  // 多留一个存 \0
    if (dest->bufferSize < maxSize)mallocSStringBuf(dest, maxSize);
    int i;
    dest->length = 0;
    for (i = 0; data[i] && i < dest->bufferSize; i++)
        dest->data[i] = data[i], dest->length++;
    dest->data[i] = 0;
}

char* getSStringData(SString* h) {
    return h->data;
}

unsigned int getSStringLength(SString* h) {
    return h->length;
}

void mallocSStringBuf(SString* h, unsigned int bufSize) {
    unsigned int cnt = bufSize / ChunkSize;
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
    unsigned int i;
    for (i = 0; l[i] && r[i] && l[i] == r[i]; i++) {}
    return l[i] == r[i];
}

