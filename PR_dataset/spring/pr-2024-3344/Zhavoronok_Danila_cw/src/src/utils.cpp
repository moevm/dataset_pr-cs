#include "../include/utils.h"

std::ostream &
operator<<(std::ostream &os, const std::vector<std::string> &val)
{
    for (auto &it : val)
        os << '<' << it << '>' << ' ';

    return os;
}

bool contains(const std::vector<std::string> &container, const std::string &key)
{
    return std::find(container.begin(), container.end(), key) != container.end();
}

bool check_rgb_val(int val)
{
    if (val >= 0 && val <= 255)
        return true;

    throw_exception("RGB value is not in range.", 43);
    return false;
}

bool check_N_val(int val)
{
    if (val >= 0)
        return true;

    throw_exception("Value is less than zero.", 44);
    return false;
}

bool no_check(int)
{
    return true;
}
