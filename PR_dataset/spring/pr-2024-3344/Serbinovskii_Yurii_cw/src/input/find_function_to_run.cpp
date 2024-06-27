#include "find_function_to_run.h"
#include "validations.h"


std::string run_this(std::unordered_map<std::string, std::string> & flags_table) {
    if (flags_table.find("info") != flags_table.end()) {
        if (validate_dependecies("info", flags_table)) {
            return "info";
        }
        else {
            std::cerr << DEPENDECIES << "info" << std::endl;
            std::cout << HELP << std::endl;
            exit(41);
        }
    }
    else if (flags_table.find("rect") != flags_table.end()) {
        if (validate_dependecies("rect", flags_table)) {
            return "rect";
        }
        else {
            std::cerr << DEPENDECIES << "rect" << std::endl;
            std::cout << HELP << std::endl;
            exit(41);
        }
    }
    else if (flags_table.find("ornament") != flags_table.end()) {
        if (validate_dependecies("ornament", flags_table)) {
            return "ornament";
        }
        else {
            std::cerr << DEPENDECIES << "ornament" << std::endl;
            std::cout << HELP << std::endl;
            exit(41);
        }
    }
    else if (flags_table.find("rotate") != flags_table.end()) {
        if (validate_dependecies("rotate", flags_table)) {
            return "rotate";
        }
        else {
            std::cerr << DEPENDECIES << "rotate" << std::endl;
            std::cout << HELP << std::endl;
            exit(41);
        }
    }
    else if (flags_table.find("circle") != flags_table.end()) {
        if (validate_dependecies("circle", flags_table)) {
            return "circle";
        }
        else {
            std::cerr << DEPENDECIES << "circle" << std::endl;
            std::cout << HELP << std::endl;
            exit(41);
        }
    }
    else if (flags_table.find("outside_ornament") != flags_table.end()) {
        if (validate_dependecies("paving", flags_table)) {
            return "outside_ornament";
        }
        else {
            std::cerr << DEPENDECIES << "rect" << std::endl;
            std::cout << HELP << std::endl;
            exit(41);
        }
    }
    else {
        std::cerr << "It seems, you forgot to enter the functions" << std::endl;
        std::cout << HELP << std::endl;
        exit(40);
    }
}