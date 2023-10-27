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
 * @file Iter.hpp
 * @author KSJ
 * @date 2023-10-27
 * @version 0.0.1
 * @brief 自定义迭代器类
 * @bug none found
 * @todo none
 * @warning some shouldn't do
*/
#pragma once
#include<concepts>
/**
 * @brief 可迭代指针类型，支持 getData(), getNext()
 * @author SJ
 * @tparam pVec 指针类型
 */
template<typename pVec>
concept Iterable = std::is_pointer<pVec>::value && requires(pVec p) {
    p->getData();
    p->getNext();
};
/**
 * @author SJ
 * @date 2023-10-27
 * @class
 * @tparam[in] pVec 指针类型,支持pVec getNext(),以及getData()
 * @tparam[in] DataType pVec 指向的数据类型[pVec->getData]
 * @brief 自定义迭代器
 * @bug no bug
 * @warning no warning
 * @todo no todo
 * @exception no exception
*/
template<Iterable pVec, typename DataType>
class Iter {
 public:
    explicit Iter(pVec p_vec):p_vec(p_vec) {}
    bool operator!=(const Iter& other) const {
        return p_vec != other.p_vec;
    }
    DataType& operator*() const {
        return this->p_vec->getData();
    }
    const Iter& operator++() {
        p_vec = p_vec->getNext();
        return *this;
    }
    pVec p_vec;
};
