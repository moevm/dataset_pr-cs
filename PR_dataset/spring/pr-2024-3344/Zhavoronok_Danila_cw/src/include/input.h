#pragma once
#include "../include/utils.h"
#include "../include/throw_exception.h"
#include <sstream>
#include <getopt.h>
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>

template <class T>
bool contains(const T &map, const std::string &key);

struct option_temp
{
    std::string long_name;
    int requires_arg;
    std::string help_info;
};

std::unordered_map<char, option_temp> gen_input_temp();
std::vector<option> gen_long_options(const std::unordered_map<char, option_temp> &input_temp);

struct arg
{
    std::vector<std::string> values;
    int count = 0;
};
std::ostream &operator<<(std::ostream &os, const arg &val);

std::unordered_map<std::string, arg> input(int argc, char **argv);

std::vector<int> parse_input(std::string input, bool (*check)(int), int required_num_of_params);

bool check_no_intersecting_flags(const std::vector<std::string> &corresponding_options, const std::unordered_map<std::string, arg> &input_data);
std::unordered_map<std::string, std::vector<std::string>> gen_corresponding_options();
std::string get_function_to_exec(std::unordered_map<std::string, arg> input_data);

void print_help();
