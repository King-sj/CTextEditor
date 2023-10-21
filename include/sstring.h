/* ==================================================================
* Copyright (c) 2023-10-20.
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
#include<stdbool.h>
#ifndef SSTRING_H_
#define SSTRING_H_
typedef struct _sstring {
    unsigned int length;  // 字符串长度
    unsigned int bufferSize;  // buffer 总大小
    char* data;  // 数据首指针
}SString;
// 获得新字符串
__declspec(dllexport) SString* newSString(int size);
// 释放字符串
__declspec(dllexport) void freeInitSString(SString* h);
// 复制字符串
__declspec(dllexport) void copySString(SString* src, SString* dest);
// 用字符数组填充字符串, data 的长度不超过 maxSize
__declspec(dllexport) void fillSString(SString* dest, char* data, unsigned int maxSize);
// 获取字符串数据
__declspec(dllexport) char* getSStringData(SString* h);
// 获取字符串长度
__declspec(dllexport) unsigned int getSStringLength(SString* h);
// 判断两个字符串是否相等
__declspec(dllexport) bool isEqualSString(SString* l, SString* r);
// 判断字符串和原生字符数组是否相等
__declspec(dllexport) bool isEqualSStringChars(SString* l, char* r);
// 判断原生字符数组是否相等
__declspec(dllexport) bool isEqualChars(char* l, char* r);

#endif  // SSTRING_H_
