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

#include<cxxopts.hpp>
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
        std::cin >> opt;
        switch (opt) {
            // TODO(SJ) 使用脚本[python]自动定义宏变量
            [[unlikely]]
            case READ_FILE:
                readFile();
                break;
            [[unlikely]]
            case QUIT:
                quit();
                break;
            [[likely]]
            case CLEAR:
                clear();
                break;
            [[likely]]
            case SHOW_MENU:
                showMenu();
                break;
            default:
                std::cout << "input is invalid" << std::endl;
        }
    }
    return 0;
}

void readFile() {
    std::string path;
    std::cin >> path;
    try {
        text.loadFile(path.c_str());
    } catch(const char* e) {
        std::cout << e << std::endl;
        return;
    }
    std::cout << "load file done" << std::endl;
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
