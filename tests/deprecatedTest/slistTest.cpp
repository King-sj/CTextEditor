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
 * @file slistTest.cpp
 * @author KSJ
 * @date 2023-10-24
 * @version 0.0.1
 * @brief 已废弃
 * @bug none found
 * @todo none
 * @warning 已废弃
*/
#include"gtest/gtest.h"
#include<slist.h>
#include<iostream>
using namespace std;
TEST(SList, String) {
    SList(char)* str = newSList(char)();
    string s = "hello world\n";
    for (const auto& ch : s) {
        SListInsertBack(char)(str, ch);
        SListMovP(char)(&str, 1);
    }
    string res;
    while (str != NULL) {
        res += *str->data;
        SListMovP(char)(&str, -1);
    }
    string ans = "\ndlrow olleh";
    EXPECT_EQ(res, ans);
}
