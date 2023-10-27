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
* @file base.h
* @author KSJ
* @date 2023-10-24
* @version 0.0.1
* @brief 公共宏、函数、常量
* @bug none found
* @todo none
* @warning some shouldn't do
*/
#pragma once
#include<time.h>
#include<concepts>
#define PrintErr(ty, Msg) \
    {time_t curtime;\
    time(&curtime);\
    fprintf(stderr, "(%s)[%s] [%s:%llu] :\n\t %s\n\n", ty, ctime(&curtime), __FILE__, __LINE__, Msg);}
/**
 * @brief 存在默认构造函数
 * @attention 指针符合要求，默认为nullptr
 * @tparam T 存在 T()
 */
template<typename T>
concept ExistDefaultConstruction = std::is_pointer<T>::value ||
    requires(T x) {
    x = T();
};
/**
 * @brief 可比较类型概念
 * @author SJ
 * @tparam T 可比较类型
 */
template<typename T>
concept CompareAble = requires(T x, T y) {
    x == y;
    x < y;
    x > y;
};
/**
 * @author SJ
 * @date 2023-10-26
 * @brief 判断 x 是否在 [l, r)
 * @tparam T 可比较大小的类型，例如 int
 * @param[in] x
 * @param[in] l 左区间
 * @param[in] r 右（开）区间
 * @retval bool
*/
template<typename T>
requires CompareAble<T>
bool isInRange(T x, T l, T r) {
    return l <= x && x < r;
}
