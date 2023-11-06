/**
 * @copyright ==================================================================
 *  Copyright (c) 2023-11-06.
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
 * @file KVector.hpp
 * @author KSJ
 * @date 2023-11-06
 * @version 0.0.1
 * @brief 动态数组
 * @bug none found
 * @todo none
 * @warning some shouldn't do
*/
template<typename T>
class KVector {
 private:
    T* data;
    size_t capacity = 1<<10;
    size_t _size = 0;
 public:
    KVector() {
        data = (T*)malloc(sizeof(T)*capacity);
    }
    ~KVector() {
        delete[] data;
        data = nullptr;
    }
    void push_back(T t) {
        if (_size == capacity) {
            capacity*=1.5;  // 1.5 is good by STL
            data = (T*)realloc(data, sizeof(T)*capacity);
        }
        data[_size] = t;
        _size++;
    }
    void erase(size_t index) {
        if (index >= _size) {
            throw "index out of range";
            return;
        }
        for (size_t i = index; i < _size-1; i++) {
            data[i] = data[i+1];
        }
        _size--;
    }
    T& operator[](size_t index) {
        if (index >= _size) {
            throw "index out of range";
            return T();
        }
        return data[index];
    }
    size_t size() {
        return _size;
    }
};
