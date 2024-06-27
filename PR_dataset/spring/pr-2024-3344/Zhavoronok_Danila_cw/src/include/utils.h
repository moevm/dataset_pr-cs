#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include "../include/throw_exception.h"

bool contains(const std::vector<std::string> &container, const std::string &key);

std::ostream &operator<<(std::ostream &os, const std::vector<std::string> &val);

bool check_rgb_val(int val);
bool check_N_val(int val);
bool no_check(int);
