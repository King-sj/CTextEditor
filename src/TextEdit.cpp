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
 * @file TextEdit.cpp
 * @author KSJ
 * @date 2023-11-01
 * @version 0.0.1
 * @brief 文本编辑类
 * @bug none found
 * @todo none
 * @warning some shouldn't do
*/
#include<TextEdit.h>
#include<fstream>
TextEdit::TextEdit() {
}
void TextEdit::loadFile(const char *fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw "open file failed";
        return;
    }
    this->clear();
    char ch;
    while (!file.eof()) {
        ch = file.get();
        if (ch == '\n') {
            this->lines.insertBack(TextLine());  // insert new line
            this->lines.toNext();
        } else {
            this->lines.getData().insertBack(ch);
            this->lines.getData().toNext();
        }
    }
    file.close();
}

void TextEdit::save(const char * fileName) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        throw "open file failed";
        return;
    }
    for (auto& line : this->lines) file << line << std::endl;
    file.close();
}

KList<TextLine>& TextEdit::getLines() {
    return this->lines;
}

void TextEdit::showText() {
    for (auto& line : this->lines) {
        for (auto& ch : line) {
            std::cout << ch;
        }
        std::cout << std::endl;
    }
}

void TextEdit::showText(int l, int r) {
    int i = 0;
    for (auto& line : this->lines) {
        i++;
        if (!isInRange(i - 1, l, r))continue;
        for (auto& ch : line) {
            std::cout << ch;
        }
        std::cout << std::endl;
    }
}

void TextEdit::insertLine(int pos, TextLine str) {
    assert(pos >= -1 && pos < (int)this->lines.getLength());
    this->lines.toHead();
    // this->lines++;
    if (pos == -1) {
        this->lines.insertPre(str);
    } else {
        for (int i = 0; i < pos; i++) this->lines++;
        this->lines.insertBack(str);
    }
}

void TextEdit::insertInline(int line, int pos, KString str) {
    assert(line >= 0 && line < (int)this->lines.getLength());
    this->lines.toHead();
    // this->lines++;
    for (int i = 0; i < line; i++)this->lines++;
    this->lines.getData().toHead();
    this->lines.getData()++;
    if (pos == -1) {
        this->lines.getData().insertPre(str);
    } else {
        for (int i = 0; i < pos; i++)this->lines.getData()++;
        this->lines.getData().insertBack(str);
    }
}

void TextEdit::eraseLine(int l, int r) {
    this->lines.toHead();

    for (int i = 0; i < l; i++) this->lines++;
    for (int i = l; i < r; i++)
        this->lines.erase();
}

void TextEdit::eraseInline(int line, int l, int r) {
    this->lines.toHead();
    for (int i = 0; i < line; i++) this->lines++;
    this->lines.getData().toHead();
    for (int i = 0; i < l; i++) this->lines.getData()++;
    for (int i = l; i < r; i++)
        this->lines.getData().erase();
}

KPoint<int32_t> TextEdit::find(KString str, int lin) {
    int l  = 0;
    int p = 0;
    for (auto& line : this->lines) {
        if (l < lin) {
            l++;
            continue;
        }
        std::cout << line << std::endl;
        p = line.find(str);
        if (p != -1) return KPoint<int32_t>(l, p);
        l++;
    }
    return KPoint<int32_t>(-1, -1);
}

void TextEdit::clear() {
    this->lines.toHead();
    this->lines.clearExceptCur();
}
