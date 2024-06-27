#include "Arguments.h"
#include "../Errors.h"
#include <getopt.h>
#include <iostream>

enum class CommandType { Info,
                         SqaredLines,
                         RgbFilter,
                         Rotate,
                         Help };

std::map<std::string_view, enum CommandType> CommandMap = {
    {"info", CommandType::Info},
    {"squared_lines", CommandType::SqaredLines},
    {"rgbfilter", CommandType::RgbFilter},
    {"rotate", CommandType::Rotate},
    {"help", CommandType::Help},
};
std::map<std::string_view, enum Rgb> RgbMap = {
    {"red", Rgb::Red},
    {"green", Rgb::Green},
    {"blue", Rgb::Blue},
};

Arguments::Arguments(int argc, char *argv[]) {
    int c;
    int option_index;
    opterr = 0;
    // clang-format off
    static struct option long_options[] = {
        {"help",            no_argument,        nullptr, 'h'},
        {"info",            no_argument,        nullptr, 0},
        {"input",           required_argument,  nullptr, 'i'},
        {"output",          required_argument,  nullptr, 'o'},
        {"squared_lines",   no_argument,        nullptr, 0},
        {"rgbfilter",       no_argument,        nullptr, 0},
        {"rotate",          no_argument,        nullptr, 0},
        {"left_up",         required_argument,  nullptr, 0},
        {"right_down",      required_argument,  nullptr, 0},
        {"side_size",       required_argument,  nullptr, 0},
        {"thickness",       required_argument,  nullptr, 0},
        {"color",           required_argument,  nullptr, 0},
        {"fill",            no_argument,        nullptr, 0},
        {"fill_color",      required_argument,  nullptr, 0},
        {"component_name",  required_argument,  nullptr, 0},
        {"component_value", required_argument,  nullptr, 0},
        {"angle",           required_argument,  nullptr, 0},
        {nullptr, 0, nullptr, 0},
    };
    // clang-format on
    while ((c = getopt_long(argc, argv, "hi:o:", long_options, &option_index)) != -1) {
        switch (c) {
            case 'h':
                raw_.insert_or_assign("command", "help");
                break;
            case 'i':
            case 'o':
                raw_.insert({long_options[option_index].name, optarg});
                break;
            case 0: {
                auto opt_name = long_options[option_index].name;
                if (CommandMap.count(opt_name))
                    raw_.insert({"command", opt_name});
                else if (optarg)
                    raw_.insert({opt_name, optarg});
                else
                    raw_.insert({opt_name, ""});
            } break;
            case '?':
            default:
                ArgERROR("unknown arg: '" << argv[optind - 1] << '\'');
                break;
        }
    }
    if (!raw_.count("command"))
        raw_.insert({"command", "help"});

    if (argc > optind) {
        if (optind + 1 == argc && raw_["command"] != "help" && !raw_.count("input"))
            raw_.insert({"input", argv[optind]});
        else
            ArgERROR("exsessive args");
    }
    if (!raw_.count("output"))
        raw_.insert({"output", "out.png"});

    if (!raw_.count("input") && raw_["command"] != "help")
        ArgERROR("missing input file");

    if (raw_["output"] == raw_["input"] && raw_["command"] != "info")
        ArgERROR("output file should not be equal input file");
}

void help() {
    std::cout << "Usage: image_tool [options] [input_file]\n"
              << "Options:\n"
              << "  -h, --help                 Show this help message and exit.\n"
              << "  --info                     Display information about the input image.\n"
              << "  -i, --input <file>         Specify the input image file.\n"
              << "  -o, --output <file>        Specify the output image file (default: out.png).\n"
              << "  --squared_lines            Draw squared lines on the image.\n"
              << "  --left_up <left>.<up>      Specify the top-left corner for squared lines or rotation.\n"
              << "  --side_size <n>            Specify the side size for squared lines.\n"
              << "  --thickness <n>            Specify the line thickness for squared lines.\n"
              << "  --color <r>.<g>.<b>        Specify the color for squared lines in RGB format.\n"
              << "  --fill                     Enable filling the squares with color.\n"
              << "  --fill_color <r>.<g>.<b>   Specify the fill color for squared lines in RGB format.\n"
              << "  --rgbfilter                Apply an RGB filter to the image.\n"
              << "  --component_name <name>    Specify the RGB component to filter (red, green, blue).\n"
              << "  --component_value <0-255>  Set the value for the RGB component filter.\n"
              << "  --rotate                   Rotate a region of the image.\n"
              << "  --right_down <right>.<down>Specify the bottom-right corner for rotation.\n"
              << "  --angle <90/180/270>       Set the rotation angle in degrees.\n"
              << "\n"
              << "Example:\n"
              << "  cw --input image.png --output edited.png --squared_lines --left_up 10.10 --side_size 100 --thickness 5 --color 255.0.0 --fill --fill_color 0.255.0\n"
              << "This command will draw a filled red square with a green fill on 'image.png' and save it as 'edited.png'.\n";
    exit(0);
};

int Arguments::parse_int_arg(std::string_view arg) {
    try {
        return std::stoi(this->raw_[arg.data()].data());
    } catch (std::exception &e) {
        ArgInvalidERROR(arg);
    }
}

void Arguments::parse_coords_arg(std::string_view arg, Coords &coords) {
    if (2 != sscanf(raw_[arg.data()].data(), "%d.%d", &coords[0], &coords[1])) {
        ArgInvalidERROR(arg);
    }
}

void Arguments::parse_color_arg(std::string_view arg, Color &color) {
    if (3 != sscanf(this->raw_[arg].data(), "%d.%d.%d", &color[0], &color[1], &color[2]))
        ArgInvalidERROR(arg);
    for (int i : color)
        if (i < 0 || i > 255)
            ArgInvalidERROR(arg);
}

// replace std::vector for std::span when using C++20
void Arguments::check_missing_args(std::vector<std::string_view> arr) {
    for (auto i : arr)
        if (!raw_.count(i.data()))
            ArgERROR("missing " << i << " argument");
}

void Arguments::parse_filter() {
    check_missing_args({"component_name", "component_value"});

    if (RgbMap.count(raw_["component_name"]))
        p_.filter.color = RgbMap[raw_["component_name"]];
    else
        ArgInvalidERROR("component_name");

    p_.filter.val = parse_int_arg("component_value");

    if (p_.filter.val < 0 || p_.filter.val > 255)
        ArgInvalidERROR("component_value");
}

void Arguments::parse_rotate() {
    check_missing_args({"left_up", "right_down", "angle"});

    parse_coords_arg("left_up", p_.rotate.coords[0]);
    parse_coords_arg("right_down", p_.rotate.coords[1]);

    if (p_.rotate.coords[0][0] > p_.rotate.coords[1][0] ||
        p_.rotate.coords[0][1] > p_.rotate.coords[1][1])
        ArgERROR("invalid coords");

    p_.rotate.angle = parse_int_arg("angle");

    if (p_.rotate.angle != 90 &&
        p_.rotate.angle != 180 &&
        p_.rotate.angle != 270)
        ArgERROR("invalid angle");
}

void Arguments::parse_sqared() {
    check_missing_args({"left_up", "side_size", "color", "thickness"});

    p_.sqared.fill = (bool)raw_.count("fill");

    if (p_.sqared.fill) {
        if (raw_.count("fill_color"))
            parse_color_arg("fill_color", p_.sqared.fill_color);
        else
            ArgERROR("missing fill_color argument");
    }
    p_.sqared.side_size = parse_int_arg("side_size");
    p_.sqared.thickness = parse_int_arg("thickness");

    parse_coords_arg("left_up", p_.sqared.coords);

    parse_color_arg("color", p_.sqared.color);

    parse_color_arg("fill_color", p_.sqared.fill_color);
}

void Arguments::process() {
    enum CommandType command = CommandMap[raw_["command"].data()];

    if (command == CommandType::Help)
        help();

    Image image(raw_["input"]);

    if (command != CommandType::Info && !image.is_valid())
        IOERROR("file is not valid");

    switch (command) {
        case CommandType::Info:
            image.info();
            exit(0);
            break;
        case CommandType::RgbFilter:
            parse_filter();
            image.rgbfilter(p_.filter.color, p_.filter.val);
            break;
        case CommandType::SqaredLines:
            parse_sqared();
            image.squared_lines(p_.sqared.coords, p_.sqared.side_size, p_.sqared.thickness,
                                p_.sqared.color, p_.sqared.fill, p_.sqared.fill_color);
            break;
        case CommandType::Rotate:
            parse_rotate();
            image.rotate(p_.rotate.coords, p_.rotate.angle);
            break;
        case CommandType::Help:
            break;
    }
    image.write(raw_["output"]);
};
