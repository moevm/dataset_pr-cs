#pragma once

#include <iostream>
#include <string>
#include <regex>
#include "../other/messages.h"
#include <unordered_map>

int value_check(std::string function, std::unordered_map<std::string, std::string> & flags_table);
int validate_dependecies(std::string function, std::unordered_map<std::string, std::string> & flags_table) ;