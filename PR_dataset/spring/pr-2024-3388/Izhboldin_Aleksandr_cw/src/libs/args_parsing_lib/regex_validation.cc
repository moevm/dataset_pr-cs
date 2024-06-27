#include "regex_validation.h"

using namespace regex_config;

bool is_valid_argument(const std::string &str, const std::string &reg_template) {
  const std::regex k_regex(reg_template, std::regex_constants::ECMAScript);

  if (std::regex_match(str, k_regex)) return true;
  return false;
}

Color parse_color(const std::string &str) {
  static const std::regex k_regex(k_color_pattern, std::regex_constants::ECMAScript);
  std::smatch results;

  Color color;
  if (std::regex_search(str, results, k_regex)) {
	color.b = std::stoi(results[k_blue]);
	color.g = std::stoi(results[k_green]);
	color.r = std::stoi(results[k_red]);
  }
  return color;
}

int parse_number(const std::string &str) {
  static const std::regex k_regex(k_positive_number_pattern, std::regex_constants::ECMAScript);
  std::smatch results;

  if (std::regex_search(str, results, k_regex)) {
	return std::stoi(results[0]);
  }

  return 0;
}

std::pair<int, int> parse_coordinates(const std::string &str) {
  static const std::regex k_regex(k_coordinates_pattern, std::regex_constants::ECMAScript);
  std::smatch results;
  std::pair<int, int> parsed(0, 0);
  if (std::regex_search(str, results, k_regex)) {
	parsed.first = std::stoi(results[k_x]);
	parsed.second = std::stoi(results[k_y]);
  }
  return parsed;
}
