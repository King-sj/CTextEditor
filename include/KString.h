/**
 * @copyright ==================================================================
 *  Copyright (c) 2023-10-27.
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
 * @file KString.h
 * @author KSJ
 * @date 2023-10-27
 * @version 0.0.1
 * @brief 字符串实现
 * @bug none found
 * @todo none
 * @warning some shouldn't do
*/
#pragma once
#include<iostream>
#include<string>
#include<unordered_set>  /// @attention this will be delete after I done KUnorderedSet
#include "KList.hpp"
/**
 * @brief 字符串类
 * @author SJ
 */
class KString :public KList<char> {
 public:
    KString();
    explicit KString(std::string s);
    explicit KString(const char*);
    friend std::ostream& operator<<(std::ostream& os, KString& h);
    friend std::istream& operator>>(std::istream& in, KString& h);
    /**
     * @brief Set the Sep object, 流输入遇到seps中的字符时将会停止读入
     * @author SJ
     * @param seps 默认为" \n\r\0"
     */
    virtual void setSep(KString seps);
    /**
     * @brief 判断ch 是否在sep中
     * @author SJ
     * @param[in] ch char型
     * @return true 在
     * @return false
     */
    virtual bool inSep(const char ch)const;
    /**
     * @brief 清空字符串
    */
    virtual void clear();
    /**
     * @brief 转为std::string
     * @author SJ
     * @return std::string
     */
    virtual std::string toString();
    /**
     * @brief fill with str
     * @author SJ
     * @param str "some string"
     */
    virtual void fill(std::string str);
    /**
     * @brief 返回第二个元素,第一个为'\0'
     *
     * @return Iter<NativeList<char>*, char>
     */
    Iter<NativeList<char>*, char> begin()override;
    /**
     * @brief 下表访问
     * @author SJ
     * @param idx
     * @return char
     */
    virtual char operator[](size_t idx);
    /**
     * @brief 返回匹配的下表
     * @author SJ
     * @param pattern 模式串
     * @return int pos
     * @attention -1 means that not found
     */
    virtual int find(KString pattern);
    /**
     * @brief Get the Length object
     * @attention 比KList<T>小1
     * @return size_t
     */
    size_t getLength()const override;

 public:
    std::unordered_set<char> sep;  // 读取到其中的字符就停止读入

 private:
    int kmp(KString str, KString pattern);
};
