#include "validations.h"


int value_check(std::string key, std::unordered_map<std::string, std::string> & flags_table)
{
    std::regex cords_reg ("^[0-9]+\\.[0-9]+$");
    std::regex color_reg ("^(([0-1]?[0-9]?[0-9])|(2[0-4][0-9])|(25[0-5]))\\.(([0-1]?[0-9]?[0-9])|(2[0-4][0-9])|(25[0-5]))\\.(([0-1]?[0-9]?[0-9])|(2[0-4][0-9])|(25[0-5]))$");
    std::regex positive_reg ("^[0-9]+$");
    

    if (key == "color" || key == "fill_color")
    {
        std::smatch color_match;
        if (std::regex_search(flags_table[key], color_match, color_reg))
        {
            return 1;
        }
        return 0;
    }
    if (key == "left_up" || key == "right_down" || key == "center")
    {
        std::smatch cords_match;
        if (std::regex_search(flags_table[key], cords_match, cords_reg))
        {
            return 1;
        }
        return 0;
    }
    if (key == "thickness" || key == "count" || key == "radius")
    {
        std::smatch positive_match;
        if (std::regex_search(flags_table[key], positive_match, positive_reg))
        {
            return 1;
        }
        return 0;
    }
    if (key == "angle")
    {
        if (flags_table[key] == "90" || flags_table[key] == "180" || flags_table[key] == "270")
        {
            return 1;
        }
        return 0;
    }
    if (key == "pattern")
    {
        if (flags_table[key] == "circle" || flags_table[key] == "semicircles" || flags_table[key] == "rectangle")
        {
            return 1;
        }
        return 0;
    }
    return 1;
}


int validate_dependecies(std::string function, std::unordered_map<std::string, std::string> & flags_table) {
    std::vector<std::string> some_keys;
    if (function == "info")
    {
        some_keys = {"info", "input"};
    }
    if (function == "rect") {
        some_keys = {"rect", "left_up", "right_down", "thickness", "color", "fill", "fill_color", "input", "output"};
    }
    if (function == "ornament") {
        some_keys = {"ornament", "pattern", "color", "thickness", "count", "input", "output"};
    }
    if (function == "rotate") {
        some_keys = {"rotate", "left_up", "right_down", "angle", "input", "output"};
    }
    if (function == "circle") {
        some_keys = {"circle", "center", "radius", "thickness", "color", "fill", "fill_color", "input", "output"};
    }
    if (function == "paving") {
        some_keys = {"outside_ornament", "thickness", "color", "input", "output"};
    }
    
    for (int i = 0; i < some_keys.size(); i++)
    {
        if (flags_table.find(some_keys[i]) != flags_table.end())
        {
            if (!value_check(some_keys[i], flags_table))
            {
                return 0;
            }
        }
        else if (some_keys[i] == "fill_color" || some_keys[i] == "fill")
        {
            continue;
        }
        else
        {
            return 0;
        }
    }

    return 1;
}
