#include "imageBMP.h"
#include "parser.h"

#include <string>
#include <string.h>
#include <regex.h>
#include <functional>

void psr::throwError(const char *message, int exit_code)
{
    printf("%s\n", message);
    exit(exit_code);
}

void psr::parseCoords(int& x, int& y, std::string& str)
{
    regex_t rx;
    regcomp(&rx, "(-?[0-9]+)\\.(-?[0-9]+)", REG_EXTENDED);

    regmatch_t groups[3];

    if (regexec(&rx, str.c_str(), 3, groups, 0) != 0) {
        throwError("Error: coords parsing failed.", PARSER_ERROR);
    }

    std::string string;

    for (int i = groups[1].rm_so; i < groups[1].rm_eo; i++) {
		string += str[i];
	}
    x = atoi(string.c_str());

    string.clear();
    for (int i = groups[2].rm_so; i < groups[2].rm_eo; i++) {
		string += str[i];
	}
    y = atoi(string.c_str());
}

void psr::parseNumber(int& number, std::string& str)
{
    regex_t rx;
    regcomp(&rx, "-?[0-9]+", REG_EXTENDED);

    if (regexec(&rx, str.c_str(), 0, NULL, 0) != 0) {
        throwError("Error: number parsing failed.", PARSER_ERROR);
    }

    number = atoi(str.c_str());
}


void psr::parseColor(ie::Color& color, std::string& str)
{
    regex_t rx;
    regcomp(&rx, "([0-9]+)\\.([0-9]+)\\.([0-9]+)", REG_EXTENDED);

    regmatch_t groups[4];

    if (regexec(&rx, str.c_str(), 4, groups, 0) != 0) {
        throwError("Error: color parsing failed.", PARSER_ERROR);
    }

    std::string string;

    for (int i = groups[1].rm_so; i < groups[1].rm_eo; i++) {
		string += str[i];
	}
    color.r = atoi(string.c_str());

    string.clear();
    for (int i = groups[2].rm_so; i < groups[2].rm_eo; i++) {
		string += str[i];
	}
    color.g = atoi(string.c_str());

    string.clear();
    for (int i = groups[3].rm_so; i < groups[3].rm_eo; i++) {
		string += str[i];
	}
    color.b = atoi(string.c_str());
}

void psr::parseComponentName(int& parameter, std::string& str)
{
    if (str == "red") {
        parameter = R_IDX;
        return;
    }
    if (str == "green") {
        parameter = G_IDX;
        return;
    }
    if (str == "blue") {
        parameter = B_IDX;
        return;
    }
    throwError("Error: component parsing failed.", PARSER_ERROR);    
}

void psr::checkValueValidity(int value, std::function<bool(int)> check_func)
{
    if (!check_func(value)) {
        throwError("Error: value parsing failed.", PARSER_ERROR);
    }
}

void psr::parseAxis(int& parameter, std::string& str)
{
    if (str == "x") {
        parameter = X_IDX;
        return;
    }
    if (str == "y") {
        parameter = Y_IDX;
        return;
    }
    throwError("Error: axis parsing failed.", PARSER_ERROR);    
}