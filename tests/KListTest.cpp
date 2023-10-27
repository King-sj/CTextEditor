/**
 * @copyright ==================================================================
 *  Copyright (c) 2023-10-26.
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
 * @file KListTest.cpp
 * @author KSJ
 * @date 2023-10-26
 * @version 0.0.1
 * @brief 链表类单元测试
 * @bug none found
 * @todo none
 * @warning some shouldn't do
*/
#include"KList.hpp"

#include"gtest/gtest.h"
#include<iostream>
/**
 * @author SJ
 * @date 2023-10-26
 * @fn KList<T>基本功能测试
 * @bug no bug
 * @warning no warning
 * @todo no todo
 * @exception no exception
*/
TEST(KList, BaseFunc) {
    KList<int> list1(2);
    list1.insertBack(2);
    list1.insertBack(3);
    EXPECT_EQ(list1.getData(), 2);
    EXPECT_EQ(list1.toNext(), true);
    EXPECT_EQ(list1.getData(), 3);
    EXPECT_EQ(list1.toNext(), true);
    EXPECT_EQ(list1.getData(), 2);
    EXPECT_EQ(list1.toNext(), false);
}

TEST(KList, FOR_IN_RANGFE) {
    KList<int> lis(0);
    EXPECT_EQ(lis.getLength(), 1);
    for (int i = 1; i < 10; i++, lis++) {
        lis.insertBack(i);
        EXPECT_EQ(lis.getLength(), i+1);
    }
    EXPECT_FALSE(lis.toNext());

    int i = 0;
    for (auto& x : lis) {
        EXPECT_EQ(x, i);
        x*=x;
        i++;
    }
    i = 0;
    for (auto x : lis) {
        EXPECT_EQ(x, i*i);
        i++;
    }
    lis.gotoP(lis.getHead());
    while (lis.getCur()) {
        if (lis.getData() > 5)lis.erase();
        else if (!lis.toNext())break;
    }
    EXPECT_EQ(lis.getLength(), 3);
    for (const auto& x : lis) {
        EXPECT_LE(lis.getData(), 5) << " data: " << lis.getData();
    }
}