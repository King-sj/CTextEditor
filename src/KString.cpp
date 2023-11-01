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
 * @file KString.cpp
 * @author KSJ
 * @date 2023-10-27
 * @version 0.0.1
 * @brief 字符串类实现
 * @todo 实现自定义vector
*/
#include "KString.h"
#include <vector>
#include <signal.h>
#include <setjmp.h>
#include <stdarg.h>

KString::KString():
    KList('\0') {
    this->setSep(KString(" \n\r\0"));
}

KString::KString(std::string s) {
    this->fill(s);
}

KString::KString(const char * arr): KString(std::string(arr)) {
}

void KString::setSep(KString seps) {
    this->sep.clear();
    for (auto ch : seps) sep.insert(ch);
}

bool KString::inSep(const char ch) const {
    return this->sep.count(ch);
}

void KString::clear() {
    this->toHead();
    this->clearExceptCur();
}

std::string KString::toString() {
    std::string res = "";
    for (const auto& x : *this) res += x;
    return res;
}

void KString::fill(std::string str) {
    this->clear();
    for (auto ch : str) {
        this->insertBack(ch);
        this->toNext();
    }
}

Iter<NativeList<char> *, char> KString::begin() {
    return Iter<NativeList<char> *, char>(this->getHead()->nxt);
}

char KString::operator[](size_t idx) {  // 0->1
    if (idx+1 > this->getLength())throw "out of range";
    auto cur = this->getCur();
    this->toHead();
    while (idx && this->toNext()) {idx--;}
    auto res = this->getNxt()->data;
    this->gotoP(cur);  // return
    return res;
}


int KString::find(KString pattern) {
    return kmp(*this, pattern);
}

size_t KString::getLength() const {
    return KList<char>::getLength()-1;
}
// 信号处理函数
void recvSignal(int sig) {
    std::cout << "received signal " << sig << std::endl;
}
int KString::kmp(KString str, KString pattern) {
    // 给信号注册一个处理函数
    signal(SIGSEGV, recvSignal);
    /**
     * @bug unknown file: Failure
     * C++ exception with description "cannot create std::vector larger than max_size()" thrown in the test body.
     * @todo fixed it
     */
    std::vector<int> nxt;
    try {
        nxt.resize(pattern.getLength());
    }catch(...) {
        std::cerr << "failed create vector<int> nxt with length of " <<
            pattern.getLength() << std::endl;
        throw "failed create vector";
    }

    if (pattern.getLength() > str.getLength())return -1;
    std::string s = str.toString();
    std::string pat = pattern.toString();
    for (int i = 1; i < pat.size(); i++) {
        for (int j = nxt[i - 1]; j >= 0;) {
            if (pat[i] == pat[j]) {
                nxt[i] = j + 1;  // 边界长度+1，也是跳过匹配的字符个数
                break;
            } else if (j == 0) {
                nxt[i] == 0;
                break;
            } else {
                j = nxt[j - 1];  // 跳,长度比指针大一，要减去(递归)
            }
        }
    }
    for (int i = 0; i < s.size() && i + pat.size() <= s.size(); i++) {
        for (int j = 0; j < pat.size() && i + j < s.size(); ) {
            if (s[i + j] == pat[j]) {
                if (j == pat.size() - 1) return i;
                j++;
            } else if (j == 0) {
                break;
            } else {
                i = i + j - nxt[j - 1];
                j = nxt[j - 1];
            }
        }
    }
    return -1;
}

std::ostream &operator<<(std::ostream &os, KString &h) {
    /// @attention 这个第一个字符将会输出'\0', 则可能会导致问题吗???
    for (auto x : h) {
        os << x;
    }
    // os << '\0';  // end
    return os;
}

std::istream &operator>>(std::istream &in, KString &h) {
    h.clear();
    char ch;
    while (in.get(ch), !h.inSep(ch)) {
        h.insertBack(ch);
        h++;
    }
    return in;
}
