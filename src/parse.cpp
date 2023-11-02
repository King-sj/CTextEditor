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
#include <iostream>
#include "base.h"
#include<menu.h>
#include<algorithm>
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

    if (existFunction("clear", result)) clear();

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
    return false;  // TODO(SJ) true or false
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
    std::cout << "\n" << std::endl;  // 多点空行， 看起来舒服
    return false;
}

int parseExec(int argc, const char* argv[]) {
    std::cout << ("(CTextEditor): ");
    cxxopts::Options options = init(argc, argv);
    if (argc > 1) {
        dealMainParse(argc, argv, options);  // deal begin parse
        std::cout << ("(CTextEditor): ");
    }
    int cnt = 1;
    std::string tmp = "";
    std::vector<std::string> parses{argv[0]};
    auto packParses = [&]()->void {
        /// convert vector<string> to char**
        char** args = (char**)malloc(sizeof(char*)*parses.size());
        for (int i = 0; i < parses.size(); i++) {
            args[i] = (char*)malloc(sizeof(char)*parses[i].length());
            strcpy(args[i], parses[i].c_str());
        }

        // deal parses
        dealMainParse(cnt, const_cast<const char**>(args), options);

        for (int i = 0; i < parses.size(); i++) {
            delete args[i];
            args[i] = nullptr;
        }
        delete args;
        args = nullptr;
    };
    char ch;
    while (true) {
        ch = std::cin.get();
        if (ch == '\n' || ch == ' ') {
            cnt++;
            parses.push_back(tmp);
            if (ch == '\n') {
                packParses();
                std::cout << ("(CTextEditor): ");
                parses.clear();
                parses.push_back(argv[0]);  // push pragma name
                cnt = 1;
            }
            tmp = "";
            continue;
        }
        tmp += ch;
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

cxxopts::Options init(int argc, const char* argv[]) {
    std::unique_ptr<cxxopts::Options> allocated(new cxxopts::Options(argv[0], " - CTextEditor console tool"));
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

        ("clear", "clear the screen");
    options.parse_positional({"Func", "positional"});

    options.add_options("Args")
        ("i,input", "Input file", cxxopts::value<std::string>())
        ("o,output", "Output file", cxxopts::value<std::string>())
        ("a, all", "select all in current all function");
    return options;
}