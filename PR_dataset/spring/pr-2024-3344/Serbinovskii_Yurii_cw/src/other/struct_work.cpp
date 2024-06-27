#include "struct_work.h"


Rectangle rect_struct(std::unordered_map<std::string, std::string> & flags_table)
{
    Rectangle rect;
    rect.left_up[0] = std::stoi(flags_table["left_up"].substr(0, flags_table["left_up"].find('.')));
    rect.left_up[1] = std::stoi(flags_table["left_up"].substr(flags_table["left_up"].find('.') + 1, std::string::npos - flags_table["left_up"].find('.')));


    rect.right_down[0] = std::stoi(flags_table["right_down"].substr(0, flags_table["right_down"].find('.')));
    rect.right_down[1] = std::stoi(flags_table["right_down"].substr(flags_table["right_down"].find('.') + 1, std::string::npos - flags_table["right_down"].find('.')));

    rect.thickness = std::stoi(flags_table["thickness"]);
    rect.color.b = std::stoi(flags_table["color"].substr(0, flags_table["color"].find('.')));
    rect.color.g = std::stoi(flags_table["color"].substr(flags_table["color"].find('.') + 1, flags_table["color"].rfind('.') - flags_table["color"].find('.')));
    rect.color.r = std::stoi(flags_table["color"].substr(flags_table["color"].rfind('.') + 1, std::string::npos - flags_table["color"].rfind('.')));
    
    if (flags_table.find("fill") != flags_table.end() && flags_table.find("fill_color") != flags_table.end())
    {
        rect.fill = 1;
        rect.fill_color.b = std::stoi(flags_table["fill_color"].substr(0, flags_table["fill_color"].find('.')));
        rect.fill_color.g = std::stoi(flags_table["fill_color"].substr(flags_table["fill_color"].find('.') + 1, flags_table["fill_color"].rfind('.') - flags_table["fill_color"].find('.')));
        rect.fill_color.r = std::stoi(flags_table["fill_color"].substr(flags_table["fill_color"].rfind('.') + 1, std::string::npos - flags_table["fill_color"].rfind('.')));
    }
    else if (flags_table.find("fill") != flags_table.end())
    {
        std::cerr << "Where is fill_color?" << std::endl;
        exit(46);
    }
    else
    {
        rect.fill = 0;
    }

    return rect;
}

Circle circ_struct(std::unordered_map<std::string, std::string> & flags_table)
{
    Circle circ;
    circ.center[0] = std::stoi(flags_table["center"].substr(0, flags_table["center"].find('.')));
    circ.center[1] = std::stoi(flags_table["center"].substr(flags_table["center"].find('.') + 1, std::string::npos - flags_table["center"].find('.')));

    circ.radius = std::stoi(flags_table["radius"]);

    circ.thickness = std::stoi(flags_table["thickness"]);
    circ.color.b = std::stoi(flags_table["color"].substr(0, flags_table["color"].find('.')));
    circ.color.g = std::stoi(flags_table["color"].substr(flags_table["color"].find('.') + 1, flags_table["color"].rfind('.') - flags_table["color"].find('.')));
    circ.color.r = std::stoi(flags_table["color"].substr(flags_table["color"].rfind('.') + 1, std::string::npos - flags_table["color"].rfind('.')));



    if (flags_table.find("fill") != flags_table.end() && flags_table.find("fill_color") != flags_table.end())
    {
        circ.fill = 1;
        circ.fill_color.b = std::stoi(flags_table["fill_color"].substr(0, flags_table["fill_color"].find('.')));
        circ.fill_color.g = std::stoi(flags_table["fill_color"].substr(flags_table["fill_color"].find('.') + 1, flags_table["fill_color"].rfind('.') - flags_table["fill_color"].find('.')));
        circ.fill_color.r = std::stoi(flags_table["fill_color"].substr(flags_table["fill_color"].rfind('.') + 1, std::string::npos - flags_table["fill_color"].rfind('.')));
    }
    else if (flags_table.find("fill") != flags_table.end())
    {
        std::cerr << "Where is fill_color?" << std::endl;
        exit(46);
    }
    else
    {
        circ.fill = 0;
    }

    return circ;
}

Ornament orn_struct(std::unordered_map<std::string, std::string> & flags_table)
{
    Ornament orn;

    orn.pattern = flags_table["pattern"];

    orn.count = std::stoi(flags_table["count"]);

    orn.thickness = std::stoi(flags_table["thickness"]);

    orn.color.b = std::stoi(flags_table["color"].substr(0, flags_table["color"].find('.')));
    orn.color.g = std::stoi(flags_table["color"].substr(flags_table["color"].find('.') + 1, flags_table["color"].rfind('.') - flags_table["color"].find('.')));
    orn.color.r = std::stoi(flags_table["color"].substr(flags_table["color"].rfind('.') + 1, std::string::npos - flags_table["color"].rfind('.')));

    return orn;
}

Rotate rot_struct(std::unordered_map<std::string, std::string> & flags_table)
{
    Rotate rot;
    rot.left_up[0] = std::stoi(flags_table["left_up"].substr(0, flags_table["left_up"].find('.')));
    rot.left_up[1] = std::stoi(flags_table["left_up"].substr(flags_table["left_up"].find('.') + 1, std::string::npos - flags_table["left_up"].find('.')));

    rot.right_down[0] = std::stoi(flags_table["right_down"].substr(0, flags_table["right_down"].find('.')));
    rot.right_down[1] = std::stoi(flags_table["right_down"].substr(flags_table["right_down"].find('.') + 1, std::string::npos - flags_table["right_down"].find('.')));

    rot.angle = std::stoi(flags_table["angle"]);

    return rot;
}

Smth smth_struct(std::unordered_map<std::string, std::string> & flags_table)
{
    Smth smth;
    
    smth.thickness = std::stoi(flags_table["thickness"]);
    smth.color.b = std::stoi(flags_table["color"].substr(0, flags_table["color"].find('.')));
    smth.color.g = std::stoi(flags_table["color"].substr(flags_table["color"].find('.') + 1, flags_table["color"].rfind('.') - flags_table["color"].find('.')));
    smth.color.r = std::stoi(flags_table["color"].substr(flags_table["color"].rfind('.') + 1, std::string::npos - flags_table["color"].rfind('.')));

    return smth;
}