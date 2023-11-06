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
 * @file parse.h
 * @author KSJ
 * @date 2023-11-02
 * @version 0.0.1
 * @brief 命令行参数处理
 * @bug none found
 * @todo none
 * @warning some shouldn't do
*/
#pragma once
#include "cxxopts.hpp"
#include <memory>
#include<string>
#include<vector>
/**
 * @brief 参数解析收尾，输出为匹配的参数等
 * @author SJ
 * @param argc 参数数量
 * @param result 参数解析结果
 */
void end_parse(int argc, cxxopts::ParseResult& result);

/**
 * @brief 处理常规参数
 * @author SJ
 * @param argc 参数数量
 * @param argv 具体参数, 其中argv[0]代表pragma name
 * @param result 解析结果
 * @param options 参数解析对象
 * @return true 解析成功
 * @return false 解析失败
 */
bool dealDefaultGroup(
    int argc, const char* argv[],
    cxxopts::ParseResult& result, cxxopts::Options& options
);
/**
 * @brief 参数解析主函数，主要负责调用其它具体的参数解析函数
 * @author SJ
 * @param argc 参数数量
 * @param argv 具体参数, argv[0]为程序名称
 * @param options 参数解析对象
 * @return true 解析成功
 * @return false 解析失败
 */
bool dealMainParse(int argc, const char* argv[], cxxopts::Options& options);
/**
 * @brief 初始化参数解析对象
 * @author SJ
 * @param argc 参数数量
 * @param argv 具体参数, argv[0]为程序名
 * @return cxxopts::Options 初始化后的参数解析对象
 */
cxxopts::Options init(int argc, const char* argv[]);
/**
 * @brief 开启参数处理事件循环
 * @author SJ
 * @param argc 初始的参数数量
 * @param argv 初始的参数，argv[0]为程序名称
 * @return int 正常执行返回 0
 */
int parseExec(int argc, const char* argv[]);
inline bool existFunction(const char* funcName, cxxopts::ParseResult& result);
/**
 * @brief 有缩写的函数的存在性检验
 * @author SJ
 * @param ch 缩写,such as 'h'
 * @param funcName 全称, such as 'help'
 * @param result 解析结果对象
 * @return true
 * @return false
 */
inline bool existFunction(const char* ch, const char* funcName, cxxopts::ParseResult& result);

/**
 * @brief 将控制台读入的命令(str)转换为char**
 * @attention 需要手动返回值释放内存
 * @author SJ
 * @param pragmaName 程序路径
 * @param str
 * @param[in] cnt 返回参数数量
 * @return char**
 */
char ** consoleStr2CharPP(const char* pragmaName, const std::string & str, int& cnt);
