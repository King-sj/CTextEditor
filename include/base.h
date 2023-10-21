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
#include<string.h>
#include<stdlib.h>
#ifndef BASE_H_
#define BASE_H_
#define Macro2Str(x) #x
// 平凡类型返回 NULL
#define newT(T) new##T
#define newNullT_IMPL(T) T* newT(T)(int) {return NULL;}

#define newTP(T) T##$
#define newNullTP_IMPL(T) T** newTP(T)(int) {T* tmp = newT(T)(0); return &tmp;}
newNullT_IMPL(int);
newNullT_IMPL(char);
newNullTP_IMPL(int);
struct SString;
SString* newTP(SString) {struct SString tmp; return &tmp;}
newNullTP_IMPL(SString);
newNullTP_IMPL(newTP(SString));

#define T_TP_IMPL newNullT_IMPL
#endif  // BASE_H_
