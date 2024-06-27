#pragma once

#include <regex>
#include <string>
#include <iostream>

#include "../bmp_image_lib/bmp_image_class.h"

namespace regex_config {
// Regex-Patterns
const std::string k_positive_number_pattern = R"(^[1-9]\d*$)";
const std::string k_coordinates_pattern = R"(^(\d+)\.(\d+)$)";
const std::string
	k_color_pattern =
	R"(^((?:2[0-5][0-9])|(?:[0-1]?[0-9]{0,2}))\.((?:2[0-5][0-9])|(?:[0-1]?\d{0,2}))\.((?:2[0-5][0-9])|(?:[0-1]?\d{0,2}))$)";

enum regex_color_pos : int {
  k_red = 1,
  k_green,
  k_blue
};

enum regex_coordinates_pos : int {
  k_x = 1,
  k_y
};
}

bool is_valid_argument(const std::string &str, const std::string &reg_template);
Color parse_color(const std::string &str);
int parse_number(const std::string &str);
std::pair<int, int> parse_coordinates(const std::string &str);
