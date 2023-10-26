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
 * @mainpage 文本编辑器
 * @file mainApp.cpp
 * @author KSJ
 * @date 2023-10-24
 * @version 0.0.2
 * @brief 文本编辑器入口文件
 * @bug 结果不符合预期
 * @todo none
 * @warning some shouldn't do
*/
#include"KList.hpp"
#include<iostream>
int main() {
    KList<int> lis(0);
    for (int i = 1; i < 10; i++, lis++) {
        lis.insertBack(i);
        // lis.setData(i*lis.getData());
    }
    // for (int i = 1; i < 10; i++) {
    //     std::cout << lis.getData() << std::endl;
    //     lis.toPre();
    // }
    int i = 0;
    for (auto& x : lis) {
        std::cout << x << std::endl;
        i++;
        if (i > 10)break;
    }
    return 0;
}
