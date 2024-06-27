#include "input/checking_flags.h"
#include "input/find_function_to_run.h"
#include "image_methods/one_class.h"
#include "other/struct_work.h"
#include "other/structs.h"
#include "other/messages.h"

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "It seems, you forgot to pick the option" << std::endl;
        std::cout << HELP << std::endl;
        exit(40);
    }


    std::unordered_map<std::string, std::string> flags_table = getFlags(argc, argv);
    
    if (flags_table.find("help") != flags_table.end())
    {
        std::cout << "Course work for option 5.1, created by Yurii Serbinovskii." << std::endl;
        std::cout << PRINT_HELP << std::endl;
        exit(0);
    }
    std::string function_to_run = run_this(flags_table);


    Image img;
    img.readBMP(flags_table["input"], function_to_run);

    if (flags_table["output"] == flags_table["input"])
    {
        std::cerr << OUTPUT << std::endl;
        exit(43);
    }

    if (function_to_run == "rect")
    {
        Rectangle rect = rect_struct(flags_table);
        img.rectangle(rect);
    }
    else if (function_to_run == "circle")
    {
        Circle circ = circ_struct(flags_table);
        img.circle(circ);
    }
    else if (function_to_run == "ornament")
    {
        Ornament orn = orn_struct(flags_table);
        img.ornament(orn);
    }
    else if (function_to_run == "rotate")
    {
        Rotate rot = rot_struct(flags_table);
        img.rotate(rot);
    }
    else if (function_to_run == "outside_ornament")
    {
        Smth smth = smth_struct(flags_table);
        img.something(smth);
    }
    img.exportBMP(flags_table["output"]);
}

