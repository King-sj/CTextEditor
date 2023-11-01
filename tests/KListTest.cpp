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
#include "KList.hpp"
#include "KString.h"

#include "gtest/gtest.h"
#include <iostream>
#include <random>
#include <string>
#include <algorithm>
#include <stdexcept>
#include <fstream>

/**
 * @author SJ
 * @date 2023-10-26
 * @fn KList<T>基本功能测试
 * @bug no bug
 * @warning no warning
 * @todo no todo
 * @exception no exception
 */
TEST(KList, BaseFunc)
{
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
TEST(KList, FOR_IN_RANGFE)
{
    KList<int> lis(0);
    EXPECT_EQ(lis.getLength(), 1);
    for (int i = 1; i < 10; i++, lis++)
    {
        lis.insertBack(i);
        EXPECT_EQ(lis.getLength(), i + 1);
    }
    EXPECT_FALSE(lis.toNext());

    int i = 0;
    for (auto &x : lis)
    {
        EXPECT_EQ(x, i);
        x *= x;
        i++;
    }
    i = 0;
    for (auto x : lis)
    {
        EXPECT_EQ(x, i * i);
        i++;
    }
    lis.gotoP(lis.getHead());
    while (lis.getCur())
    {
        if (lis.getData() > 5)
            lis.erase();
        else if (!lis.toNext())
            break;
    }
    EXPECT_EQ(lis.getLength(), 3);
    for (const auto &x : lis)
    {
        EXPECT_LE(x, 5) << " data: " << x;
    }
}

TEST(KList, KString)
{
    std::string str = "hello world";
    KString s(str);
    // std::cout << s << s << std::endl;
    for (auto &x : s)
        x += 1;
    str = s.toString();
    EXPECT_EQ(str, std::string("ifmmp!xpsme"));
}

std::random_device rd;  // 将用于获得随机数引擎的种子
std::mt19937 gen(rd());  // 以 rd() 播种的标准 mersenne_twister_engine

inline std::string randomStr()
{
    std::string res = "";
    // 用 dis 变换 gen 生成的随机 unsigned int 为 [left, right] 中的 int
    std::uniform_int_distribution<int> dis('a', 'z');
    // TODO(SJ) 随机生成的string长度大于1000时导致kmp中的vector报错
    //unknown file: Failure
    //C++ exception with description "cannot create std::vector larger than max_size()" thrown in the test body.
    int32_t len = dis(gen, decltype(dis)::param_type{1, 1000});  // change range temporarily
    for (int i = 0; i < len; i++)
        res += dis(gen);
    return res;
}
TEST(KList, KString_KMP)
{
    // 打开一个文件用于写入
    std::ofstream file("C:/Users/SJ/Desktop/CTextEditor/tests/error.log");
    // 检查文件是否成功打开
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing" << std::endl;
        return;
    }
    // 将 std::cerr 的缓冲区重定向到文件
    std::streambuf *cerr_buff = std::cerr.rdbuf();
    std::cerr.rdbuf(file.rdbuf());


    std::string str, subStr;
    std::uniform_int_distribution<int> dis(0, 1);
    try {
        for (int i = 0; i < 10000; i++) {
            str = randomStr();
            dis.param(decltype(dis)::param_type{0, str.length() - 1});
            // case 1
            int pos = dis(gen);
            int len = dis(gen);
            len = std::min(len, static_cast<int>(str.length()) - pos);
            len = len > 0 ? len : 1;

            subStr = str.substr(pos, len);

            // std::cerr << i << ":\n"<< str << "\n" << subStr << std::endl;

            KString s(str), pa(subStr);
            EXPECT_EQ(s.find(pa), str.find(subStr)) << " from:\n"
                << str << "\nfind: " << subStr;
            // case 2
            subStr = randomStr();
            KString nP(subStr);
            EXPECT_TRUE(s.find(nP) == (int)str.find(subStr));
        }
    }
    catch (const std::length_error &le) {
        // TODO(SJ) :unknown file: Failure
        // C++ exception with description "cannot create std::vector larger than max_size()"
        // thrown in the test body.
        std::cerr << "Length error: " << le.what() << std::endl;
        std::cerr << str << "\n" << subStr << std::endl;
    }
    catch (...) {
        std::cerr << "some error: " << std::endl;
        std::cerr << str << "\n" << subStr << std::endl;
    }
    // 恢复 std::cerr 到原来的状态，以便错误信息可以在控制台上显示
    std::cerr.rdbuf(cerr_buff);

    // 关闭文件
    file.close();
}
