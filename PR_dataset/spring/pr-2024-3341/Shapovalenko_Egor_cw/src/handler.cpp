#include "handler.h"
#include "parser.h"

#include <getopt.h>
#include <stdio.h>
#include <map>
#include <string>
#include <set>
#include <algorithm>


hdlr::Handler::Handler() :
    flags{
        {HELP_IDX,               {0, ""}},
        {INPUT_IDX,              {0, ""}},
        {OUTPUT_IDX,             {0, ""}},
        {INFO_IDX,               {0, ""}},

        {THICKNESS_IDX,          {0, ""}},
        {COLOR_IDX,              {0, ""}},
        {FILL_IDX,               {0, ""}},
        {FILL_COLOR_IDX,         {0, ""}},

        {BORDER_RECTS_IDX,       {0, ""}},
        {BORDER_COLOR_IDX,       {0, ""}},

        {CIRCLE_IDX,             {0, ""}},
        {CENTER_IDX,             {0, ""}},
        {RADIUS_IDX,             {0, ""}},

        {RGBFILTER_IDX,          {0, ""}},
        {COMPONENT_NAME_IDX,     {0, ""}},
        {COMPONENT_VALUE_IDX,    {0, ""}},

        {SPLIT_IDX,              {0, ""}},
        {NUMBER_X_IDX,           {0, ""}},
        {NUMBER_Y_IDX,           {0, ""}},

        {CONCAT_IDX,             {0, ""}},
        {AXIS_IDX,               {0, ""}},
        {INPUT_SECOND_IDX,       {0, ""}},
    },
    short_options("hi:o:"),
    long_options{
        {"help",            no_argument,          NULL,    HELP_IDX},
        {"input",           required_argument,    NULL,    INPUT_IDX},
        {"output",          required_argument,    NULL,    OUTPUT_IDX},
        {"info",            no_argument,          NULL,    INFO_IDX},

        {"thickness",       required_argument,    NULL,    THICKNESS_IDX},
        {"color",           required_argument,    NULL,    COLOR_IDX},
        {"fill",            no_argument,          NULL,    FILL_IDX},
        {"fill_color",      required_argument,    NULL,    FILL_COLOR_IDX},

        {"filled_rects",    no_argument,          NULL,    BORDER_RECTS_IDX},
        {"border_color",    required_argument,    NULL,    BORDER_COLOR_IDX},
        
        {"circle",          no_argument,          NULL,    CIRCLE_IDX},
        {"center",          required_argument,    NULL,    CENTER_IDX},
        {"radius",          required_argument,    NULL,    RADIUS_IDX},
        
        {"rgbfilter",       no_argument,          NULL,    RGBFILTER_IDX},
        {"component_name",  required_argument,    NULL,    COMPONENT_NAME_IDX},
        {"component_value", required_argument,    NULL,    COMPONENT_VALUE_IDX},
        
        {"split",           no_argument,          NULL,    SPLIT_IDX},
        {"number_x",        required_argument,    NULL,    NUMBER_X_IDX},
        {"number_y",        required_argument,    NULL,    NUMBER_Y_IDX},

        {"concat",          no_argument,          NULL,    CONCAT_IDX},
        {"axis",            required_argument,    NULL,    AXIS_IDX},
        {"input_second",    required_argument,    NULL,    INPUT_SECOND_IDX},

        {NULL,              0,                    NULL,    0}
    }
{}

hdlr::Handler::~Handler() = default;

void hdlr::Handler::show_author_info(const char *option, const char *name, const char *surname)
{
    printf("Course work for option %s, created by %s %s\n", option, name, surname);
}

void hdlr::throwError(const char *message, int exit_code)
{
    printf("%s\n", message);
    exit(exit_code);
}

void hdlr::Handler::getFlags(int argc, char **argv)
{   
    opterr = 0;
    int option;
    while ((option = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
        if (flags.find(option) != flags.end()) {
            flags[option].entered = true;
            if (optarg) {
                flags[option].parameter = optarg;
            }
        } else {
            throwError("Error: wrong flag.", HANDLER_ERROR);
        }
    }
    last_argument = argv[argc-1];
}

std::set<int> hdlr::Handler::getRedundantFlags(std::set<int>& required_flags, 
    std::set<int>& optional_flags)
{
    std::set<int> redundant_flags;

    for (auto i : flags) {
        if (required_flags.find(i.first) == required_flags.end() && 
            optional_flags.find(i.first) == optional_flags.end()) {
            redundant_flags.insert(i.first);
        }
    }

    return redundant_flags;
}

bool hdlr::Handler::checkFlagCompliance(std::set<int>& required_flags, std::set<int>& redundant_flags) {
    bool all_required_entered = true;
    for (auto i : required_flags) {
        all_required_entered &= flags[i].entered;
    }

    bool all_redundant_not_entered = true;
    for (auto i : redundant_flags) {
        all_redundant_not_entered &= !flags[i].entered;
    }
    return all_required_entered && all_redundant_not_entered;
}

void hdlr::Handler::getFinFoutNames(std::string &input_file_name, std::string &output_file_name)
{
    if (flags[INPUT_IDX].entered) {
        input_file_name = flags[INPUT_IDX].parameter;
    } else {
        input_file_name = last_argument;
    }

    if (flags[OUTPUT_IDX].entered) {
        output_file_name = flags[OUTPUT_IDX].parameter;
    }
}

void hdlr::Handler::getSecondFinName(std::string &second_file_name)
{
    if (flags[INPUT_SECOND_IDX].entered) {
        second_file_name = flags[INPUT_SECOND_IDX].parameter;
    }
}

bool hdlr::Handler::isHelp()
{
    std::set<int> required_flags = {};
    std::set<int> optional_flags = {HELP_IDX};
    std::set<int> redundant_flags = getRedundantFlags(required_flags, optional_flags);
    return checkFlagCompliance(required_flags, redundant_flags);
}

bool hdlr::Handler::isInfo()
{
    std::set<int> required_flags = {INFO_IDX};
    std::set<int> optional_flags = {INPUT_IDX};
    std::set<int> redundant_flags = getRedundantFlags(required_flags, optional_flags);
    return checkFlagCompliance(required_flags, redundant_flags);
}

bool hdlr::Handler::isBorderRectangles()
{
    std::set<int> required_flags = {BORDER_RECTS_IDX, COLOR_IDX, BORDER_COLOR_IDX, THICKNESS_IDX};
    std::set<int> optional_flags = {INPUT_IDX, OUTPUT_IDX};
    std::set<int> redundant_flags = getRedundantFlags(required_flags, optional_flags);
    return checkFlagCompliance(required_flags, redundant_flags);
}

bool hdlr::Handler::isCircle()
{
    std::set<int> required_flags = {CIRCLE_IDX, CENTER_IDX, RADIUS_IDX, THICKNESS_IDX, COLOR_IDX};
    std::set<int> optional_flags = {INPUT_IDX, OUTPUT_IDX, FILL_IDX, FILL_COLOR_IDX};
    std::set<int> redundant_flags = getRedundantFlags(required_flags, optional_flags);
    return checkFlagCompliance(required_flags, redundant_flags) && !(flags[FILL_IDX].entered && !flags[FILL_COLOR_IDX].entered);
}

bool hdlr::Handler::isRGBFilter()
{
    std::set<int> required_flags = {RGBFILTER_IDX, COMPONENT_NAME_IDX, COMPONENT_VALUE_IDX};
    std::set<int> optional_flags = {INPUT_IDX, OUTPUT_IDX};
    std::set<int> redundant_flags = getRedundantFlags(required_flags, optional_flags);
    return checkFlagCompliance(required_flags, redundant_flags);
}

bool hdlr::Handler::isSplit()
{
    std::set<int> required_flags = {SPLIT_IDX, NUMBER_X_IDX, NUMBER_Y_IDX, THICKNESS_IDX, COLOR_IDX};
    std::set<int> optional_flags = {INPUT_IDX, OUTPUT_IDX};
    std::set<int> redundant_flags = getRedundantFlags(required_flags, optional_flags);
    return checkFlagCompliance(required_flags, redundant_flags);
}

bool hdlr::Handler::isConcat()
{
    std::set<int> required_flags = {CONCAT_IDX, AXIS_IDX, INPUT_SECOND_IDX, COLOR_IDX};
    std::set<int> optional_flags = {INPUT_IDX, OUTPUT_IDX};
    std::set<int> redundant_flags = getRedundantFlags(required_flags, optional_flags);
    return checkFlagCompliance(required_flags, redundant_flags);
}

void hdlr::Handler::doHelp()
{
    printf("--help (-h)            Prints the help\n");
    printf("--input (-i)           Sets the name of the input image. If the flag is omitted, it is assumed that the name of the input image is passed as the last argument\n");
    printf("--output (-o)          Sets the name of the output image. If the flag is omitted, it is assumed that the name of the input image is out.bmp\n");
    printf("--info                 Prints information about the image\n");
    printf("\n");

    printf("Basic flags:\n");
    printf("--thickness            Line thickness. Format: NUMBER\n");
    printf("--color                Line color. Format: RED.GREEN.BLUE\n");
    printf("--fill                 Works as a binary value: there is a flag - true, there is no flag - false\n");
    printf("--fill_color           Fill color. Can be used without --fill flag. Format: RED.GREEN.BLUE\n");
    printf("\n");

    printf("--filled_rects         Drawing a border for all rectangles filled with specified color. Required: --color, --border_color, --thickness\n");
    printf("--color                Color that rectangles are filled with. Format: RED.GREEN.BLUE\n");
    printf("--border_color         Color of the border. Format: RED.GREEN.BLUE\n");
    printf("\n");

    printf("--circle               Drawing a circle. Required: --center, --radius, --thickness, --color. Optional: --fill, --fill_color\n");
    printf("--center               Coordinates of the center. Format: x.y\n");
    printf("--radius               Radius. Format: NUMBER\n");
    printf("\n");

    printf("--rgbfilter            RGB filter component\n");
    printf("--component_name       Which component needs to be changed. Format: {red || green || blue}\n");
    printf("--component_value      To which value it needs to be changed. Format: NUMBER\n");
    printf("\n");
    
    printf("--split                Divides the image into number_y*number_x parts. Required: --thickness, --color\n");
    printf("--number_x             The number of parts along the Y-axis. Format: NUMBER\n");
    printf("--number_y             The number of parts along the X-axis. Format: NUMBER\n");
    printf("\n");

    printf("--concat               Сoncatenates to given images with alternating pixels along specified axis. Empty spaces are filled with specified color. Required: --axis, --input_second, --color\n");
    printf("--input_second         Sets the name of the image to concatenate with.\n");
    printf("--axis                 Along which axis to concatenate. Format: {x || y}\n");
    printf("\n");
}

void hdlr::Handler::doInfo()
{
    std::string input_file_name;
    
    if (flags[INPUT_IDX].entered) {
        input_file_name = flags[INPUT_IDX].parameter;
    } else {
        input_file_name = last_argument;
    }

    ie::ImageBMP image_bmp;
    image_bmp.readImageFromFile(input_file_name.c_str());
    image_bmp.showImageInfo();
}

void hdlr::Handler::doBorderRectangles()
{
    int thickness;
    ie::Color rectangles_color, border_color;
    std::string input_file_name;
    std::string output_file_name = "out.bmp";

    psr::parseNumber(thickness, flags[THICKNESS_IDX].parameter);
    psr::parseColor(rectangles_color, flags[COLOR_IDX].parameter);
    psr::parseColor(border_color, flags[BORDER_COLOR_IDX].parameter);
    getFinFoutNames(input_file_name, output_file_name);

    psr::checkValueValidity(thickness, [](int thickness) { return (thickness > 0); });

    ie::ImageBMP image_bmp;
    image_bmp.readImageFromFile(input_file_name.c_str());
    image_bmp.borderRectangles(rectangles_color, border_color, thickness);
    image_bmp.writeImageToFile(output_file_name.c_str());
}

void hdlr::Handler::doCircle()
{
    int x0, y0, radius, thickness;
    bool fill;
    ie::Color color, fill_color;
    std::string input_file_name;
    std::string output_file_name = "out.bmp";

    psr::parseCoords(x0, y0, flags[CENTER_IDX].parameter);
    psr::parseNumber(radius, flags[RADIUS_IDX].parameter);
    psr::parseNumber(thickness, flags[THICKNESS_IDX].parameter);
    psr::parseColor(color, flags[COLOR_IDX].parameter);
    fill = flags[FILL_IDX].entered;
    if (fill) {
        psr::parseColor(fill_color, flags[FILL_COLOR_IDX].parameter);
    }
    getFinFoutNames(input_file_name, output_file_name);
    
    psr::checkValueValidity(radius, [](int radius) { return (radius > 0); });
    psr::checkValueValidity(thickness, [](int thickness) { return (thickness > 0); });

    ie::ImageBMP image_bmp;
    image_bmp.readImageFromFile(input_file_name.c_str());
    image_bmp.drawCircle(x0, y0, radius, thickness, color, fill, fill_color);
    image_bmp.writeImageToFile(output_file_name.c_str());
}

void hdlr::Handler::doRGBFilter()
{
    int component_idx, component_value;
    std::string input_file_name;
    std::string output_file_name = "out.bmp";

    psr::parseComponentName(component_idx, flags[COMPONENT_NAME_IDX].parameter);
    psr::parseNumber(component_value, flags[COMPONENT_VALUE_IDX].parameter);
    getFinFoutNames(input_file_name, output_file_name);

    psr::checkValueValidity(component_value, [](int component_value) { return (component_value >= 0 && component_value <= 255); });    

    ie::ImageBMP image_bmp;
    image_bmp.readImageFromFile(input_file_name.c_str());
    image_bmp.rgbFilter(component_idx, component_value);
    image_bmp.writeImageToFile(output_file_name.c_str());
}

void hdlr::Handler::doSplit()
{
    int number_x, number_y, thickness;
    ie::Color color;
    std::string input_file_name;
    std::string output_file_name = "out.bmp";
    
    psr::parseNumber(number_x, flags[NUMBER_X_IDX].parameter);
    psr::parseNumber(number_y, flags[NUMBER_Y_IDX].parameter);
    psr::parseNumber(thickness, flags[THICKNESS_IDX].parameter);
    psr::parseColor(color, flags[COLOR_IDX].parameter);
    getFinFoutNames(input_file_name, output_file_name);

    psr::checkValueValidity(number_x, [](int number_x) { return (number_x > 1); });
    psr::checkValueValidity(number_y, [](int number_y) { return (number_y > 1); });
    psr::checkValueValidity(thickness, [](int thickness) { return (thickness > 0); });

    ie::ImageBMP image_bmp;
    image_bmp.readImageFromFile(input_file_name.c_str());

    for(int i = 1; i < number_y; i++) {
        int y = (image_bmp.getHeight() / number_y) * i;
        for (int j = 0; j <= thickness/2; j++) {
            image_bmp.drawLine(0, y-j, image_bmp.getWidth()-1, y-j, 1, color);
            image_bmp.drawLine(0, y+j, image_bmp.getWidth()-1, y+j, 1, color);
        }
    }

    for(int i = 1; i < number_x; i++) {
        int x = (image_bmp.getWidth() / number_x) * i;
        for (int j = 0; j <= thickness/2; j++) {
            image_bmp.drawLine(x-j, 0, x-j, image_bmp.getHeight()-1, 1, color);
            image_bmp.drawLine(x+j, 0, x+j, image_bmp.getHeight()-1, 1, color);
        }
    }

    // for (int y = image_bmp.getHeight() / number_y; y < image_bmp.getHeight(); y += std::max(1, image_bmp.getHeight() / number_y)) {
    //     for (int i = 0; i <= thickness/2; i++) {
    //         image_bmp.drawLine(0, y-i, image_bmp.getWidth()-1, y-i, 1, color);
    //         image_bmp.drawLine(0, y+i, image_bmp.getWidth()-1, y+i, 1, color);
    //     }
    // }
    
    // for (int x = image_bmp.getWidth() / number_x; x < image_bmp.getWidth(); x += std::max(1, image_bmp.getWidth() / number_x)) {
    //     for (int i = 0; i <= thickness/2; i++) {
    //         image_bmp.drawLine(x-i, 0, x-i, image_bmp.getHeight()-1, 1, color);
    //         image_bmp.drawLine(x+i, 0, x+i, image_bmp.getHeight()-1, 1, color);
    //     }
    // }

    image_bmp.writeImageToFile(output_file_name.c_str());
}

void hdlr::Handler::doConcat()
{
    int axis_idx;
    ie::Color fill_color;
    std::string input_file_name;
    std::string second_file_name;
    std::string output_file_name = "out.bmp";

    psr::parseAxis(axis_idx, flags[AXIS_IDX].parameter);
    psr::parseColor(fill_color, flags[COLOR_IDX].parameter);
    getFinFoutNames(input_file_name, output_file_name);
    getSecondFinName(second_file_name);

    ie::ImageBMP image_bmp;
    image_bmp.readImageFromFile(input_file_name.c_str());

    ie::ImageBMP second_image_bmp;
    second_image_bmp.readImageFromFile(second_file_name.c_str());

    image_bmp.concatBMP(second_image_bmp, axis_idx, fill_color);
    image_bmp.writeImageToFile(output_file_name.c_str());
}

void hdlr::Handler::handleFlags()
{
    if (isHelp()) {
        doHelp();
    } else if (isInfo()) {
        doInfo();
    } else if (isBorderRectangles()) {
        doBorderRectangles();
    } else if (isCircle()) {
        doCircle();
    } else if (isRGBFilter()) {
        doRGBFilter();
    } else if (isSplit()) {
        doSplit();
    } else if (isConcat()){
        doConcat();
    } else {
        throwError("Error: invalid set of flags.", HANDLER_ERROR);
    }
}