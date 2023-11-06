/**
 * @copyright ==================================================================
 *  Copyright (c) 2023-11-05.
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
 * @file KPoint.h
 * @author KSJ
 * @date 2023-11-05
 * @version
 * @brief 点类
 * @bug none found
 * @todo none
 * @warning some shouldn't do
*/
#include<iostream>
template<typename T>
struct KPoint {
    T x;
    T y;
    KPoint(T x, T y) : x(x), y(y) {}
    friend std::ostream& operator<<(std::ostream& os, const KPoint<T>& p) {
        os << "(" << p.x << "," << p.y << ")";
        return os;
    }
};
