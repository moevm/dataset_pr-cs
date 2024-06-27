#include "operation_params.hpp"
#include "logger.hpp"
#include "messages.hpp"

std::vector<int> parse_values(const std::string& str)
{
    std::vector<int> values;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, '.'))
    {
        try
        {
            values.push_back(std::stoi(token));
        }
        catch (const std::invalid_argument& e)
        {
            Logger::exit(ERR_INVALID_ARGUMENT, invalid_argument_error + token );
        }
    }
    return values;
}

RGB parse_RGB(const std::string& str)
{
    std::vector<int> values = parse_values(str);
    if (values.size() != 3) { Logger::exit(ERR_INVALID_ARGUMENT, invalid_color_format_error); }
    for (int value : values)
    {
        if (value < 0 || value > 255) { Logger::exit(ERR_INVALID_ARGUMENT, invalid_color_range_error + std::to_string(value)); }
    }
    return { static_cast<uint8_t>(values[0]), static_cast<uint8_t>(values[1]), static_cast<uint8_t>(values[2]) };
}

Coordinate parseCoordinate(const std::string& str)
{
    Coordinate coord;
    std::vector<int> values = parse_values(str);
    if (values.size() != 2) { Logger::exit(ERR_INVALID_ARGUMENT, invalid_color_format_error); }
    coord.x = values[0];
    coord.y = values[1];
    return coord;
}

void display_help()
{
    Logger::log(help_usage_description);
    Logger::log(help_usage_start);
    Logger::log(mirror_option_description);
    Logger::log(axis_option_description);
    Logger::log(left_up_option_description);
    Logger::log(right_down_option_description);
    Logger::log(dest_left_up_option_description);
    Logger::log(old_color_option_description);
    Logger::log(new_color_option_description);
    Logger::log(color_option_description);
    Logger::log(copy_option_description);
    Logger::log(color_replace_option_description);
    Logger::log(split_option_description);
    Logger::log(number_x_option_description);
    Logger::log(number_y_option_description);
    Logger::log(thickness_option_description);
    Logger::log(output_option_description);
    Logger::log(input_option_description);
    Logger::log(help_option_description);
}

Operations parse_command_line(int argc, char* argv[])
{
    Operations params;

    const std::map<int, std::function<void(const char*)>> optionHandlers = {
        { 'h',
          [&](const char*)
          {
              if (argc != 2) Logger::exit(ERR_INVALID_ARGUMENT, invalid_argument_error + "--help (-h)");
              display_help();
              Logger::exit(EXIT_SUCCESS, "");
          } },
        { 'i', [&](const char* option_argument) { params.input_file = option_argument; } },
        { 'o', [&](const char* option_argument) { params.output_file = option_argument; } },
        { 256, [&](const char*) { params.mirror = true; } },
        { 257,
          [&](const char* option_argument)
          {
              if (strcmp(option_argument, "x") != 0 && strcmp(option_argument, "y") != 0) Logger::exit(ERR_INVALID_ARGUMENT, invalid_argument_error + "--axis (x/y)");
              params.axis = option_argument;
          } },
        { 258, [&](const char* option_argument) { params.left_up = parseCoordinate(option_argument); } },
        { 259, [&](const char* option_argument) { params.right_down = parseCoordinate(option_argument); } },
        { 260, [&](const char* option_argument) { params.dest_left_up = parseCoordinate(option_argument); } },
        { 261, [&](const char* option_argument) { params.old_color = parse_RGB(option_argument); } },
        { 262, [&](const char* option_argument) { params.new_color = parse_RGB(option_argument); } },
        { 263, [&](const char* option_argument) { params.line_color = parse_RGB(option_argument); } },
        { 264, [&](const char*) { params.copy = true; } },
        { 265, [&](const char*) { params.color_replace = true; } },
        { 266, [&](const char*) { params.split = true; } },
        { 267, [&](const char* option_argument) { params.number_x = parse_values(option_argument)[0]; } },
        { 268, [&](const char* option_argument) { params.number_y = parse_values(option_argument)[0]; } },
        { 269, [&](const char* option_argument) { params.thickness = parse_values(option_argument)[0]; } },
        { 270, [&](const char*) { params.info = true; } },
        { 271, [&](const char*) { Logger::set_colors_enabled(true); } },
        { 272, [&](const char*) { params.outside_ornament = true; } },
      
    };

    const char* short_options = "hi:o:";

    static struct option long_options[] = { { "help", no_argument, nullptr, 'h' }, { "input", required_argument, nullptr, 'i' }, { "output", required_argument, nullptr, 'o' }, { "mirror", no_argument, nullptr, 256 }, { "axis", required_argument, nullptr, 257 }, { "left_up", required_argument, nullptr, 258 }, { "right_down", required_argument, nullptr, 259 }, { "dest_left_up", required_argument, nullptr, 260 }, { "old_color", required_argument, nullptr, 261 }, { "new_color", required_argument, nullptr, 262 }, { "color", required_argument, nullptr, 263 }, { "copy", no_argument, nullptr, 264 }, { "color_replace", no_argument, nullptr, 265 }, { "split", no_argument, nullptr, 266 }, { "number_x", required_argument, nullptr, 267 }, { "number_y", required_argument, nullptr, 268 }, { "thickness", required_argument, nullptr, 269 }, { "info", no_argument, nullptr, 270 }, { "colorful", no_argument, nullptr, 271 },{ "outside_ornament", no_argument, nullptr, 272 }, { nullptr, 0, nullptr, 0 } };

    int opt;

    while ((opt = getopt_long(argc, argv, short_options, long_options, nullptr)) != -1)
    {
        auto handler = optionHandlers.find(opt);
        if (handler != optionHandlers.end()) { handler->second(optarg); }
    }

    if (params.mirror && params.copy) { Logger::exit(ERR_INVALID_ARGUMENT, double_function_use_err); }

    if (params.input_file.empty())
    {
        if (optind == argc - 1) { params.input_file = argv[optind]; }
        else if (optind < argc - 1) { Logger::exit(ERR_INVALID_ARGUMENT, too_many_args_err); }
        else { Logger::exit(ERR_INVALID_ARGUMENT, invalid_bmp_message); }
    }

    if (params.input_file == params.output_file) { Logger::exit(ERR_INVALID_ARGUMENT, same_input_output_message); }

    return params;
}