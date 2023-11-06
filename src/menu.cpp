/**
 * @copyright ==================================================================
 *  Copyright (c) 2023-11-02.
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
 * @file menu.cpp
 * @author KSJ
 * @date 2023-11-02
 * @version 定义
 * @brief 菜单实现
 * @bug none found
 * @todo none
 * @warning some shouldn't do
*/
#include<stdlib.h>
#include<menu.h>
#include<iostream>
#include<algorithm>
#include<cxxopts.hpp>
#include"KStack.hpp"

void init() {
    menu.loadFile(RESOURCE_PATH "MainMenu");
    showMenu();
}

inline void showMenu() {
    menu.showText();
}

int exec() {
    int opt;
    while (true) {
        /**
         * @brief 以下实现不够modern,已废弃
         *
         */
        /* std::cin >> opt;
         * switch (opt) {
         *     // TODO(SJ) 使用脚本[python]自动定义宏变量
         *     [[unlikely]]
         *     case READ_FILE:
         *         readFile();
         *         break;
         *     [[unlikely]]
         *     case QUIT:
         *         quit();
         *         break;
         *     [[likely]]
         *     case CLEAR:
         *         clear();
         *         break;
         *     [[likely]]
         *     case SHOW_MENU:
         *         showMenu();
         *         break;
         *     default:
         *         std::cout << "input is invalid" << std::endl;
         * }
         */

    }
    return 0;
}

void showText(int l, int r) {
    std::cout << whiteBegin;
    if (l < 0 || r < 0 || l > r) return;
    text.showText(l, std::min(r, int(text.getLines().getLength())));  /// @attention this maybe caused some bug
    std::cout << colorEnd;
}

void insertLine(int pos, TextLine str) {
    text.insertLine(pos, str);
}

void insertInline(int line, int pos, KString str) {
    text.insertInline(line , pos, str);
}

void eraseLine(int l, int r) {
    text.eraseLine(l, r);
}

void eraseInline(int line, int l, int r) {
    text.eraseInline(line, l, r);
}

void find(KString str, int line) {
    auto res = text.find(str, line);
    if (res.x == -1 || res.y == -1) {
        std::cout << redBegin << "not found" << colorEnd << std::endl;
        return;
    }
    std::cout << greenBegin << "(line, pos) : " << res \
    << colorEnd << std::endl;
}

void save(const char *fileName) {
    text.save(fileName);
}

bool checkBracket() {
    KStack<char> stack_1, stack_2;
    // check () {}
    for (auto& line : text.getLines())
    for (auto& ch : line) {
        if (ch == '(')stack_1.push(ch);
        if (ch == '{')stack_2.push(ch);
        if (ch == ')') {
            if (stack_1.empty()) return false;
            stack_1.pop();
        }
        if (ch == '}') {
            if (stack_2.empty()) return false;
            stack_2.pop();
        }
    }
    if (stack_1.empty() && stack_2.empty()) return true;
    return false;
}

void readFile(KString file) {
    std::string path = file.toString();
    try {
        text.loadFile(path.c_str());
    } catch(const char* e) {
        std::cout << e << std::endl;
        return;
    }
    std::cout << greenBegin <<"load file done" << colorEnd << std::endl;
}

void quit() {
    exit(0);
}

void clear() {
    #ifdef WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
