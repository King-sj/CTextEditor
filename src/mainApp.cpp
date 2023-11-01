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
 * @mainpage 文本编辑器
 * @file mainApp.cpp
 * @author KSJ
 * @date 2023-10-24
 * @version 0.0.2
 * @brief 文本编辑器入口文件
 * @bug 结果不符合预期
 * @todo none
 * @warning some shouldn't do
 */
#include "KString.h"
#include <iostream>
#include <string>
#include "../include/RBTree.hpp"
struct T
{
    int v;
    T(int v) : v(v) {}
    friend bool operator<(const T &l, const T &r)
    {
        return l.v < r.v;
    }
    friend bool operator==(const T &l, const T &r)
    {
        return l.v == r.v;
    }
    friend bool operator<=(const T &l, const T &r)
    {
        return l < r || l == r;
    }
    friend bool operator>(const T &l, const T &r)
    {
        return !(l <= r);
    }
};
redblacktree<T> t;
int main()
{
    // t.insert(1);
    // t.insert(3);
    // t.insert(7);
    // std::cout << (*t.kth(2)).v << std::endl;
    std::string str = "hyhdxxeztnzhsofqetokoytnwaiygitsffkcbgrgrveabmampyypcpkheaetzvltgnyzaygqeuluaevzsmptadpiymfbiziesqhvvpfcgxpdfcpoxxnvxydwslctsunodeinfcwsioxluxsnhomkdrykhasrkdfhyzcvnqcawtyyjnvoawbdxvzcjrswwpietphqdhiwbxtzssjrldfoeizndoipbtmgaluwgjmssfzyrxivbhhaonwmjgwhfjbtmdxivolnlqzavfqjjlfyvthxffqftyfqorjldwtsquxshaamufrkzwigcoyedblgnkpxbwgoklmlkidyejtxdplwcyhxwlknkbbharqmtqvwefynsokrebocggnxoqyiny";
    std::string subStr = "ydwslctsunodeinfcwsioxluxsnhomkdrykhasrkdfhyzcvnqcawtyyjnvoawbdxvzcjrswwpietphqdhiwbxtzssjrldfoeizndoipbtmgaluwgjmssfzyrxivbhhaonwmjgwhfjbtmdxivolnlqzavfqjjlfyvthxffqftyfqorjldwtsquxshaamufrkzwigcoyedblgnkpxbwgoklmlkidyejtxdplwcyhxwlknkbbharqmtqvwefynsokrebocggnxoqyiny";
    auto pa = KString(subStr);
    auto fa = KString(str);
    std::cout << str.size() << " " << subStr.size()  << std::endl;
    std::cout  << str.find(subStr)  << std::endl;
    std::cout << fa.getLength() << " " << pa.getLength() << std::endl;
    std::cout << fa.find(pa) << std::endl;
    assert(str == fa.toString());
    assert(subStr == pa.toString());
    return 0;
}
