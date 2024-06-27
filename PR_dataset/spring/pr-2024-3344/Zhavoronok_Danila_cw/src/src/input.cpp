#include "../include/input.h"
#include <iostream>
#include <getopt.h>
#include <string>

std::ostream &
operator<<(std::ostream &os, const arg &val)
{
    os << val.values << val.count;

    return os;
}

template <class T>
bool contains(const T &map, const std::string &key)
{
    return map.find(key) != map.end();
}

std::unordered_map<char, option_temp> gen_input_temp()
{
    std::unordered_map<char, option_temp> input_temp;

    input_temp['t'] = {"triangle", no_argument, "Draw triangle flag."};
    input_temp['p'] = {"points", required_argument, "Triangle vertices coordinates. Format: <x1.y1.x2.y2.x3.y3>"};
    input_temp['k'] = {"thickness", required_argument, "Border line thickness. Format: n > 0"};
    input_temp['c'] = {"color", required_argument, "Color of the line. Format: <rrr.ggg.bbb>, where each component is in range [0, 255]"};
    input_temp['f'] = {"fill", no_argument, "Fill triangle background flag."};
    input_temp['i'] = {"fill_color", required_argument, "Color of the backgroud. Format: identic to --color"};

    input_temp['r'] = {"biggest_rect", no_argument, "Find the biggest rectangle of a specified color and recolor it flag."};
    input_temp['o'] = {"old_color", required_argument, "Color to search the biggest rect. Format: identic to --color"};
    input_temp['n'] = {"new_color", required_argument, "Color to recolor the biggest rect to. Format: identic to --color"};

    input_temp['g'] = {"collage", no_argument, "Make collage flag."};
    input_temp['y'] = {"number_y", required_argument, "Number of times to repeat the image on the Y axis. Format: n > 0"};
    input_temp['x'] = {"number_x", required_argument, "Number of times to repeat the image on the X axis. Format: n > 0"};

    input_temp['l'] = {"line", no_argument, "Draw line flag."};
    input_temp['s'] = {"start", required_argument, "Start point coordinates. Format: x.y"};
    input_temp['e'] = {"end", required_argument, "End point coordinates. Format: x.y"};

    input_temp['I'] = {"input", required_argument, "Path to provided image. Format: filepath"};
    input_temp['O'] = {"output", required_argument, "Path to output image. Format: filepath"};
    input_temp['H'] = {"help", no_argument, "Displays this message."};

    input_temp['R'] = {"rhombus", no_argument, "Fill rhombus flag."};

    return input_temp;
}

std::vector<option> gen_long_options(const std::unordered_map<char, option_temp> &input_temp)
{
    std::vector<option> long_options;

    for (const auto &it : input_temp)
    {
        const auto &key = it.first;
        const auto &val = it.second;

        long_options.push_back({val.long_name.c_str(), val.requires_arg, 0, key});
    }
    long_options.push_back({0, 0, 0, 0});

    return long_options;
}

std::vector<int> parse_input(std::string input, bool (*check)(int), int required_num_of_params)
{
    std::istringstream ss(input);
    std::string token;
    std::vector<int> array;
    while (std::getline(ss, token, '.'))
    {
        std::istringstream sstemp(token);
        std::string temp_str;
        int temp = 0;
        try
        {
            sstemp >> temp_str;
            temp = stoi(temp_str);
        }
        catch (const std::exception &e)
        {
            throw_exception("Use int values.", 42);
        }
        check(temp);
        array.push_back(temp);
    }

    if (array.size() != required_num_of_params)
        throw_exception("Num of params isn't equal to " + std::to_string(required_num_of_params) + ".", 48);
    return array;
}

std::unordered_map<std::string, arg> input(int argc, char **argv)
{
    auto input_temp = gen_input_temp();
    auto long_options = gen_long_options(input_temp);

    std::unordered_map<std::string, arg> input_data;

    int c;
    while (1)
    {
        int option_index = 0;
        c = getopt_long(argc, argv, "tp:k:c:fi:r:o:n:g:y:x:l:s:e:I:O:R", long_options.data(), &option_index);

        if (c == -1)
            break;

        auto option_data = input_temp[c];

        if (!contains(input_data, option_data.long_name))
            input_data[option_data.long_name] = arg();

        input_data[option_data.long_name].count++;
        if (option_data.requires_arg)
            input_data[option_data.long_name].values.push_back(optarg);
    }

    return input_data;
}

bool check_no_intersecting_flags(const std::vector<std::string> &corresponding_options, const std::unordered_map<std::string, arg> &input_data)
{
    std::vector<std::string> entered_params;
    for (const auto &it : input_data)
    {
        const auto &key = it.first;
        if (!contains(corresponding_options, key))
            throw_exception("Unnecessary arguments detected, exiting.", 41);

        entered_params.push_back(key);
    }

    for (auto &key : corresponding_options)
    {
        bool is_required = key != "fill" && key != "fill_color" && key != "output"; // THE ONLY OPTIONAL ARGUMENTS

        if (is_required && !contains(entered_params, key))
            throw_exception("Not all required " + corresponding_options[0] + " arguments were provided.", 42);
    }

    return true;
}

std::unordered_map<std::string, std::vector<std::string>> gen_corresponding_options()
{
    std::unordered_map<std::string, std::vector<std::string>> corresponding_options;
    corresponding_options["triangle"] = {"triangle", "points", "thickness", "color", "fill", "fill_color", "input", "output"};
    corresponding_options["biggest_rect"] = {"biggest_rect", "old_color", "new_color", "input", "output"};
    corresponding_options["collage"] = {"collage", "number_x", "number_y", "input", "output"};
    corresponding_options["line"] = {"line", "start", "end", "thickness", "color", "input", "output"};
    corresponding_options["help"] = {"help"};
    corresponding_options["rhombus"] = {"rhombus", "color", "input", "output"};

    return corresponding_options;
}

std::string get_function_to_exec(std::unordered_map<std::string, arg> input_data)
{
    auto corresponding_options = gen_corresponding_options();
    std::string function_to_exec;
    for (const auto &it : corresponding_options)
    {
        const auto &key = it.first;
        const auto &val = it.second;
        if (contains(input_data, key) && check_no_intersecting_flags(val, input_data))
        {
            function_to_exec = key;
        }
    }

    return function_to_exec;
}

void print_help()
{
    auto input_temp = gen_input_temp();
    std::unordered_map<std::string, option_temp> input_temp_string_hash;
    for (const auto &it : input_temp)
    {
        const auto &opt = it.second;
        input_temp_string_hash[opt.long_name] = opt;
    }

    std::cout << "Course work for option 5.14, created by Zhavoronok Danila.\n";
    auto corresponding_options = gen_corresponding_options();
    for (const auto &it : corresponding_options)
    {
        const auto &options = it.second;
        for (const auto &opt_name : options)
        {
            const auto &opt = input_temp_string_hash[opt_name];
            if (opt.long_name != it.first)
                std::cout << '\t';
            std::cout << "--" << opt.long_name << " (" << opt.help_info << ")\n";
        }
        std::cout << '\n';
    }
}
