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
 * @file parse.cpp
 * @author KSJ
 * @date 2023-11-02
 * @version 0.0.1
 * @brief 命令行参数解析实现
 * @bug none found
 * @todo none
 * @warning some shouldn't do
*/
#include<parse.h>
#include<iostream>
#include<algorithm>
#include "base.h"
#include "menu.h"

void end_parse(int argc, cxxopts::ParseResult& result) {
    std::cout << "\nArguments remain = " << argc << std::endl;

    auto arguments = result.arguments();
    std::cout << "Saw " << arguments.size() << " arguments" << std::endl;
    if (result.unmatched().size() > 0)
    std::cout << redBegin <<"Unmatched options: ";
    for (const auto& option : result.unmatched()) {
        std::cout << "'" << option << "' ";
    }
    std::cout << colorEnd << std::endl;
}

bool dealDefaultGroup(
    int argc, const char* argv[],
    cxxopts::ParseResult& result, cxxopts::Options& options
) {
    if (existFunction("h", "help", result)) {
        if (result.count("all")) {
            std::cout << options.help() << std::endl;
        } else {
            std::cout << options.help({""}) << std::endl;  // default group
        }
        return true;
    }

    if (existFunction("q", "quit", result)) exit(0);

    if (existFunction("clear", result)) {
        clear();
        return true;
    }

    if (existFunction("read", result)) {
        if (result.count("input")) {
            readFile(KString(result["input"].as<std::string>()));
        } else {
            std::cout << redBegin << "No input file" << colorEnd << std::endl;
            return false;
        }
        return true;
    }
    if (existFunction("show", result)) {
        int l = 0;
        int r = INT_MAX;  /// @attention this maybe not good
        if (result.count("left")) l = result["left"].as<int32_t>();
        if (result.count("right")) r = result["right"].as<int32_t>();
        showText(l, r);
        return true;
    }

    auto positional2Str = [&]()->std::string {
        std::string res = "";
        for (
            const auto& str :
            result["positional"].as<std::vector<std::string>>())
        res += str + ",";
        res.erase(res.length()-1);  // erase ','
        return res;
    };
    if (existFunction("insert", result)) {
        std::string res = positional2Str();
        if (result.count("in")) insertInline(
            result["line"].as<int32_t>(),
            result["pos"].as<int32_t>(),
            KString(res));
        else
            insertLine(
                result["line"].as<int32_t>(),
                TextLine(res));
        return true;
    }

    if (existFunction("erase", result)) {
        int l = 0;
        int r = INT_MAX;  /// @attention this maybe not good
        if (result.count("left")) l = result["left"].as<int32_t>();
        if (result.count("right")) r = result["right"].as<int32_t>();

        if (result.count("in"))
            eraseInline(result["line"].as<int32_t>(), l, r);
        else
            eraseLine(l, r);
        return true;
    }

    if (existFunction("find", result)) {
        std::string res = positional2Str();
        find(KString(res), result["line"].as<int32_t>());
        return true;
    }

    if (existFunction("save", result)) {
        save(result["output"].as<std::string>().c_str());
        return true;
    }

    if (existFunction("checkBracket", result)) {
        if (checkBracket()) {
            std::cout << greenBegin << "Bracket is correct"
            << colorEnd << std::endl;
        } else {
            std::cout << redBegin << "Bracket is incorrect"
            << colorEnd << std::endl;
        }
        return true;
    }

    if (result.count("input")) {
        std::cout << "Input = " << result["input"].as<std::string>()
            << std::endl;
    }

    if (result.count("output")) {
        std::cout << "Output = " << result["output"].as<std::string>()
            << std::endl;
    }

    if (result.count("positional")) {
        std::cout << "Positional = {";
        auto& v = result["positional"].as<std::vector<std::string>>();
        for (const auto& s : v) {
            std::cout << s << ", ";
        }
        std::cout << "}" << std::endl;
    }

    std::cout << redBegin << "This func : '" << result["Func"].as<std::string>()
        << "' not exist, using 'help --all' to views all function and args" << colorEnd
        << std::endl;
    return false;
}

bool dealMainParse(int argc, const char* argv[], cxxopts::Options& options) {
  try {
    auto result = options.parse(argc, argv);  // deal parse
    dealDefaultGroup(argc, argv, result, options);
    end_parse(argc, result);
  } catch (const cxxopts::exceptions::exception& e) {
    std::cout << "error parsing options: " << e.what() << "\n" <<std::endl;
    return false;
  }
    std::cout << colorEnd << std::endl;  // 多点空行， 看起来舒服, 恢复默认颜色
    return false;
}

int parseExec(int argc, const char* argv[]) {
    std::cout << ("(CTextEditor): ");
    cxxopts::Options options = init(argc, argv);
    if (argc > 1) {
        dealMainParse(argc, argv, options);  // deal begin parse
        std::cout << ("(CTextEditor): ");
    }
    std::string line;
    int32_t cnt = 0;
    while (true) {
        std::getline(std::cin, line);
        cnt = 0;
        char** args = consoleStr2CharPP(argv[0], line, cnt);
        // for (int i = 0; i < cnt; i++) {
        //     std::cout << args[i] << " ";
        // }
        dealMainParse(cnt, const_cast<const char**>(args), options);
        for (int i = 0; i < cnt; i++) {
            delete args[i];
            args[i] = nullptr;
        }
        delete args;
        args = nullptr;
        std::cout << ("(CTextEditor): ");
    }
    return 0;
}

inline bool existFunction(const char * funcName, cxxopts::ParseResult& result) {
    return
    result.count(funcName) ||
    result.count("Func") && result["Func"].as<std::string>() == funcName;
}

inline bool existFunction(const char* ch, const char * funcName, cxxopts::ParseResult & result) {
    return existFunction(funcName, result) || existFunction(ch, result);
}

char ** consoleStr2CharPP(const char* pragmaName, const std::string & str, int& cnt) {
    std::string tmp = "";
    std::vector<std::string> parses{pragmaName};
    cnt = 1;
    auto push = [&]() {
        if (tmp.size() == 0) return;
        cnt++;
        parses.push_back(tmp);
        tmp = "";
    };
    char ch;
    for (int i = 0; i < str.size(); i++) {
        ch = str[i];
        if (ch == ' ') {
            push();
            continue;
        }
        if (ch == '"') {
            push();
            while (i < str.size()) {
                i++;
                ch = str[i];
                if (ch == '"') {
                    push();
                    break;
                }
                if (ch == '\\') {  // 转义
                    i++;
                    tmp += str[i];  // 直接转义，暂不支持特殊字符的转义
                    continue;
                }
                tmp += ch;
            }
            push();
            continue;
        }
        tmp += ch;
    }
    push();  // push 最后一个参数
    // convert vector<string> to char**
    char** res = (char**)malloc(sizeof(char*) * (cnt + 1));
    for (int i = 0; i < cnt; i++) {
        res[i] = (char*)malloc(sizeof(char) * (parses[i].size() + 1));
        strcpy(res[i], parses[i].c_str());
    }
    return res;
}

cxxopts::Options init(int argc, const char* argv[]) {
    std::unique_ptr<cxxopts::Options> allocated(new cxxopts::Options("CTextEditor", " - CTextEditor console tool"));
    cxxopts::Options& options = *allocated;

    options.custom_help("custom help\n\n");

    options.positional_help("FunctionName [optional args]\n"
    "in options of below without name, you should use by function name directly without '--' or maybe get wrong\n"
    "Such as 'help' or 'h' but '--help' or '-h'\n")
    .show_positional_help();

    options.set_width(70)
        .set_tab_expansion()
        .allow_unrecognised_options();

    options.add_options()
        ("F,Func", "Function, such as help, clear, readFile in below, "
        "but you shouldn't use it in reason that it's default or you will get some wrong."
        , cxxopts::value<std::string>())

        ("h, help", "Print help, use help --all show all documents")

        ("positional",
        "Positional arguments: these are the arguments that are entered "
        "without an option", cxxopts::value<std::vector<std::string>>())

        ("q, quit", "exit program")

        ("clear", "clear the screen")

        ("read", "read file\n" "example:\n read -i \"./a.txt\"")

        ("show", "example:\n" "show -l 0 -r 10"
        "show the data from [l,r),  l is 0 default, r is end default")

        ("insert", "insertBack to object\n"
        "example:\n insert --line 0 \"text\"\n"
        "insert --in --line 0 --pos 0 \"text\"\n"
        "if u wanna insert in the begin, please using \"-1\" emplace(attention:\" is must), default is begin")

        ("erase", "erase some,\n example:\n"
        "erase --in -l 0 -r 1")

        ("find", "find str in file\n begin form line" "example:\n"
        "find \"some str\" --line 0")

        ("save", "save file" "example:\n"
        "save -o \"file path\"")

        ("checkBracket", "Check for bracket matches\n"
        "example:\n"
        "checkBracket");
    options.parse_positional({"Func", "positional"});

    options.add_options("Args")
        ("i,input", "Input file", cxxopts::value<std::string>())
        ("o,output", "Output file", cxxopts::value<std::string>())
        ("a, all", "select all in current all function")
        ("l, left", "the left of range", cxxopts::value<int32_t>()->default_value("0"))
        ("r, right", "the right of range", cxxopts::value<int32_t>())
        ("pos", "the position of line", cxxopts::value<int32_t>()->default_value("0"))
        ("line", "the number of line", cxxopts::value<int32_t>()->default_value("0"))
        ("in", "inner the object", cxxopts::value<bool>()->default_value("0"), "0 or 1");
    return options;
}
