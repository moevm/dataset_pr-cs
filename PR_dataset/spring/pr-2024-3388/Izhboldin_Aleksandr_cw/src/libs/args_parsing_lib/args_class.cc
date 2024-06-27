#include "args_class.h"

using namespace args_config;

Args::Args(int argc, char **argv) {
  int option_index = 0;
  int arg_code = 0;

  static struct option long_options[] = {
	  {k_help, no_argument, nullptr, k_short_help},
	  {k_input, required_argument, nullptr, k_short_input},
	  {k_output, required_argument, nullptr, k_short_output},
	  {k_info, no_argument, &info, true},
	  {k_rectangle, no_argument, &rectangle, true},
	  {k_ornament, no_argument, &ornament, true},
	  {k_rotate, no_argument, &rotate, true},
	  {k_circle, no_argument, &circle, true},
	  {k_left_up, required_argument, &arg_code, static_cast<int>(ArgCodes::k_left_up)},
	  {k_right_down, required_argument, &arg_code, static_cast<int>(ArgCodes::k_right_down)},
	  {k_center, required_argument, &arg_code, static_cast<int>(ArgCodes::k_center)},
	  {k_thickness, required_argument, &arg_code, static_cast<int>(ArgCodes::k_thickness)},
	  {k_color, required_argument, &arg_code, static_cast<int>(ArgCodes::k_color)},
	  {k_count, required_argument, &arg_code, static_cast<int>(ArgCodes::k_count)},
	  {k_radius, required_argument, &arg_code, static_cast<int>(ArgCodes::k_radius)},
	  {k_pattern, required_argument, &arg_code, static_cast<int>(ArgCodes::k_pattern)},
	  {k_angle, required_argument, &arg_code, static_cast<int>(ArgCodes::k_angle)},
	  {k_fill, no_argument, &fill, 1},
	  {k_fill_color, required_argument, &arg_code, static_cast<int>(ArgCodes::k_fill_color)},

      {k_concat, no_argument, &concat, true},
      {k_axis, required_argument, &arg_code, static_cast<int>(ArgCodes::k_axis)},
      {k_input_second, required_argument, &arg_code, static_cast<int>(ArgCodes::k_input_second)},

      {k_circle_pixel, no_argument, &circle_pixel, true},
      {k_size, required_argument, &arg_code, static_cast<int>(ArgCodes::k_size)},
      {k_circle_color, required_argument, &arg_code, static_cast<int>(ArgCodes::k_circle_color)},

	  {nullptr, 0, nullptr, 0}
  };

  while (true) {
	int opt = getopt_long(argc, argv, k_short_options, long_options, &option_index);
	if (opt == -1) break;

	switch (opt) {
	  case k_short_help: std::cout << k_help_text;
		help = true;
		return;
	  case k_short_input: input_file = optarg;
		break;
	  case k_short_output: output_file = optarg;
		break;
	  case k_short_unknown: throw ArgsExceptions(arg_errors::k_error_unknown_arg);
	  case k_short_missing: throw ArgsExceptions(arg_errors::k_error_missing_arg);
	}

    parse_long_argument(arg_code);

	arg_code = 0;
  }

  if (input_file.empty()) {
	if (optind < argc) {
	  input_file = argv[argc - 1];
	} else {
	  throw ArgsExceptions(arg_errors::k_error_no_input_file);
	}
  }

  check_arguments();
}

void Args::parse_long_argument(int &arg_code) {
  switch (arg_code) {
    case static_cast<int>(ArgCodes::k_left_up):parse_left_up_arg();
      break;
    case static_cast<int>(ArgCodes::k_right_down):parse_right_down_arg();
      break;
    case static_cast<int>(ArgCodes::k_center): parse_center_arg();
      break;
    case static_cast<int>(ArgCodes::k_thickness):parse_thickness_arg();
      break;
    case static_cast<int>(ArgCodes::k_radius):parse_radius_arg();
      break;
    case static_cast<int>(ArgCodes::k_angle):parse_angle_arg();
      break;
    case static_cast<int>(ArgCodes::k_pattern):parse_pattern_arg();
      break;
    case static_cast<int>(ArgCodes::k_count):parse_count_arg();
      break;
    case static_cast<int>(ArgCodes::k_color):parse_color_arg();
      break;
    case static_cast<int>(ArgCodes::k_fill_color):parse_fill_color_arg();
      break;
    case static_cast<int>(ArgCodes::k_axis):parse_axis_arg();
      break;
    case static_cast<int>(ArgCodes::k_input_second):
      input_second_file = optarg;
      break;
    case static_cast<int>(ArgCodes::k_circle_color):parse_circle_color_arg();
      break;
    case static_cast<int>(ArgCodes::k_size):parse_size_arg();
      break;
  }
}
void Args::parse_size_arg() {
  if (is_valid_argument(optarg, regex_config::k_positive_number_pattern)) {
    size = parse_number(optarg);
  } else {
    throw ArgsExceptions(arg_errors::k_error_not_correct_arg_val, k_fill_color);
  }
}
void Args::parse_circle_color_arg() {
  if (is_valid_argument(optarg, regex_config::k_color_pattern)) {
    circle_color = parse_color(optarg);
    is_circle_color_set_ = true;
  } else {
    throw ArgsExceptions(arg_errors::k_error_not_correct_arg_val, k_fill_color);
  }
}
void Args::parse_axis_arg() {
  if (!strcmp(optarg, "x") || !strcmp(optarg, "y")){
    if (!strcmp(optarg, "x")) axis = 0;
    else axis = 1;
  } else {
    throw ArgsExceptions(arg_errors::k_error_not_correct_arg_val, k_fill_color);
  }
}
void Args::parse_fill_color_arg() {
  if (is_valid_argument(optarg, regex_config::k_color_pattern)) {
    fill_color = parse_color(optarg);
    is_fill_color_set_ = true;
  } else {
    throw ArgsExceptions(arg_errors::k_error_not_correct_arg_val, k_fill_color);
  }
}
void Args::parse_color_arg() {
  if (is_valid_argument(optarg, regex_config::k_color_pattern)) {
    color = parse_color(optarg);
    is_color_set_ = true;
  } else {
    throw ArgsExceptions(arg_errors::k_error_not_correct_arg_val, k_color);
  }
}
void Args::parse_count_arg() {
  if (is_valid_argument(optarg, regex_config::k_positive_number_pattern))
    count = parse_number(optarg);
  else
    throw ArgsExceptions(arg_errors::k_error_not_correct_arg_val, k_count);
}
void Args::parse_pattern_arg() {
  if (is_ok_pattern(optarg))
    pattern = ornaments::kPatterns.at(optarg);
  else
    throw ArgsExceptions(arg_errors::k_error_not_correct_arg_val, k_pattern);
}
void Args::parse_angle_arg() {
  if (is_valid_argument(optarg, regex_config::k_positive_number_pattern))
    angle = parse_number(optarg);
  else
    throw ArgsExceptions(arg_errors::k_error_not_correct_arg_val, k_angle);
}
void Args::parse_radius_arg() {
  if (is_valid_argument(optarg, regex_config::k_positive_number_pattern))
    radius = parse_number(optarg);
  else
    throw ArgsExceptions(arg_errors::k_error_not_correct_arg_val, k_radius);
}
void Args::parse_thickness_arg() {
  if (is_valid_argument(optarg, regex_config::k_positive_number_pattern))
    thickness = parse_number(optarg);
  else
    throw ArgsExceptions(arg_errors::k_error_not_correct_arg_val, k_thickness);
}
void Args::parse_center_arg() {
  if (is_valid_argument(optarg, regex_config::k_coordinates_pattern)) {
    center = parse_coordinates(optarg);
    is_center_set_ = true;
  } else {
    throw ArgsExceptions(arg_errors::k_error_not_correct_arg_val, k_center);
  }
}
void Args::parse_right_down_arg() {
  if (is_valid_argument(optarg, regex_config::k_coordinates_pattern)) {
    right_down = parse_coordinates(optarg);
    is_right_down_set_ = true;
  } else {
    throw ArgsExceptions(arg_errors::k_error_not_correct_arg_val, k_right_down);
  }
}
void Args::parse_left_up_arg() {
  if (is_valid_argument(optarg, regex_config::k_coordinates_pattern)) {
    left_up = parse_coordinates(optarg);
    is_left_up_set_ = true;
  } else {
    throw ArgsExceptions(arg_errors::k_error_not_correct_arg_val, k_left_up);
  }
}

bool Args::check_arguments() {

  if (info) {
	return true;
  }

  if ((rectangle + ornament + rotate + circle + concat + circle_pixel != 1)) { // only one functions must be selected
	throw ArgsExceptions(arg_errors::k_error_multifunction);
  }

  if (is_coordinates_set()) {
	if (left_up.first > right_down.first) std::swap(left_up.first, right_down.first);
	if (left_up.second < right_down.second) std::swap(left_up.second, right_down.second);
  } else {
	if (rectangle || rotate)
	  throw ArgsExceptions(arg_errors::k_error_not_enough_args);
  }

  if (rectangle && (!is_coordinates_set() || !thickness || !is_color_set_ || !is_fill_set())) {
	throw ArgsExceptions(arg_errors::k_error_not_enough_args, k_rectangle);
  }
  if (ornament) {
	if (pattern == ornaments::k_rectangle && (!thickness || !count || !is_color_set_))
	  throw ArgsExceptions(arg_errors::k_error_not_enough_args, k_ornament);
	else if (pattern == ornaments::k_semicircle && (!thickness || !count || !is_color_set_))
	  throw ArgsExceptions(arg_errors::k_error_not_enough_args, k_ornament);
	else if (pattern == ornaments::k_circle && !is_color_set_)
	  throw ArgsExceptions(arg_errors::k_error_not_enough_args, k_ornament);
  }
  if (rotate && (!is_coordinates_set() || !angle)) {
	throw ArgsExceptions(arg_errors::k_error_not_enough_args, k_rotate);
  }
  if (circle && (!is_center_set_ || !thickness || !radius || !is_color_set_ || !is_fill_set())) {
	throw ArgsExceptions(arg_errors::k_error_not_enough_args, k_circle);
  }

  if (input_file == output_file) {
	throw ArgsExceptions(arg_errors::k_error_input_output_same_file);
  }

  return true;
}

void Args::print_info() const {
  printf("Help %d\n", help);
  printf("Rectangle %d\n", rectangle);
  printf("Ornament %d\n", ornament);
  printf("Rotate %d\n", rotate);
  printf("Circle %d\n", circle);
  printf("left_up x: %d, y: %d\n", left_up.first, left_up.second);
  printf("right_down x: %d, y: %d\n", right_down.first, right_down.second);
  printf("center x: %d, y: %d\n", center.first, center.second);
  printf("radius %d\n", radius);
  printf("thickness %d\n", thickness);
  printf("count %d\n", count);
  printf("pattern %d\n", pattern);
  printf("angle %d\n", angle);
  printf("color r:%d g:%d b:%d \n", color.r, color.g, color.b);
  printf("fill %d\n", fill);
  printf("fill_color r:%d g:%d b:%d \n", fill_color.r, fill_color.g, fill_color.b);
  printf("input_file %s\n", input_file.c_str());
  printf("output_file %s\n", output_file.c_str());
}

bool Args::is_coordinates_set() const {
  return is_left_up_set_ && is_right_down_set_;
}

bool Args::is_fill_set() const {
  return (is_fill_color_set_ == fill) || (is_fill_color_set_);
}

bool Args::is_ok_pattern(const std::string &str) {
  if (ornaments::kPatterns.find(str) != ornaments::kPatterns.end())
	return true;
  return false;
}

