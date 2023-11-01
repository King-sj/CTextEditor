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

void TextEdit::clear() {
    this->lines.toHead();
    this->lines.clearExceptCur();
}
