/**
 * @copyright ==================================================================
 *  Copyright (c) 2023-11-01.
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
 * @file menu.h
 * @author KSJ
 * @date 2023-11-01
 * @version 0.0.1
 * @brief 菜单的宏定义
 * @bug none found
 * @todo none
 * @warning some shouldn't do
*/
#pragma once
#include<TextEdit.h>

#define READ_FILE 1
#define QUIT 9
#define CLEAR 10
#define SHOW_MENU 11
#ifndef RESOURCE_PATH
    #define RESOURCE_PATH ""
#endif

static TextEdit menu, text;
/**
 * @brief 初始化
 * @author SJ
 */
void init();
void update();
void readFile();
void quit();
void clear();
__attribute((__always_inline__))
void showMenu();
/**
 * @brief 事件循环
 * @author SJ
 * @return int 正常退出返回0
 */
int exec();
