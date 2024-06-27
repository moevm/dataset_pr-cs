#include "../include/opts_reader.hpp"

const option OptsReader::long_opts[] = {
        {"inverse", no_argument, nullptr, 0},
        {"left_up", required_argument, nullptr, 1},
        {"right_down", required_argument, nullptr, 2},
        {"gray", no_argument, nullptr, 3},
        {"resize", no_argument, nullptr, 4},
        {"left", required_argument, nullptr, 5},
        {"right", required_argument, nullptr, 6},
        {"above", required_argument, nullptr, 7},
        {"below", required_argument, nullptr, 8},
        {"color", required_argument, nullptr, 9},
        {"line", no_argument, nullptr, 10},
        {"start", required_argument, nullptr, 11},
        {"end", required_argument, nullptr, 12},
        {"thickness", required_argument, nullptr, 13},
        {"help", no_argument, nullptr, 'h'},
        {"info", no_argument, nullptr, 14},
        {"output", required_argument, nullptr, 'o'},
        {"input", required_argument, nullptr, 'i'},
        {"outside_ornament", no_argument, nullptr, 15},
};



std::vector<int32_t> OptsReader::getValues(std::string arg) {
    std::vector<int32_t> values;
    std::string token;
    std::stringstream ss(arg);
    while (std::getline(ss, token, '.'))
    {
        int32_t value = std::stoi(token);
        values.push_back(value);
    }
    return values;
}

Coordinate OptsReader::getCoordinate(std::string arg) {
    std::vector<int32_t> values = getValues(arg);
    if (values.size()!=2) throw std::runtime_error("One of coordinates have not enough args!");
    return {values[0],values[1]};
}

Color OptsReader::getColor(std::string arg){
    std::vector<int32_t> values = getValues(arg);
    if (values.size() != 3) throw std::runtime_error("Wrong number of params for color");
    for (int value : values){
        if (value < 0 || value > 255) throw std::runtime_error("Wrong color range!");
    }
    return { static_cast<uint8_t>(values[0]), static_cast<uint8_t>(values[1]), static_cast<uint8_t>(values[2]) };
}

Opts OptsReader::getOpts(int argc, char **argv) {
    int opt;
    Opts opts{};

    while ((opt = getopt_long(argc, argv, "hi:o:", long_opts, nullptr)) != -1) {
        switch (opt) {
            case 0:
                opts.inverse = true;
                break;
            case 1:
                opts.left_up = getCoordinate(optarg);
                break;
            case 2:
                opts.right_down = getCoordinate(optarg);
                break;
            case 3:
                opts.gray = true;
                break;
            case 4:
                opts.resize = true;
                break;
            case 5:
                opts.left = std::stoi(optarg);
                break;
            case 6:
                opts.right = std::stoi(optarg);
                break;
            case 7:
                opts.above = std::stoi(optarg);
                break;
            case 8:
                opts.below = std::stoi(optarg);
                break;
            case 9:
                opts.color = getColor(optarg);
                break;
            case 10:
                opts.line = true;
                break;
            case 11:
                opts.start = getCoordinate(optarg);
                break;
            case 12:
                opts.end = getCoordinate(optarg);
                break;
            case 13:
                opts.thickness = std::stoi(optarg);
                break;
            case 'h':
                opts.help = true;
                return opts;
            case 14:
                opts.info = true;
                break;
            case 'o':
                opts.output_file = optarg;
                break;
            case 'i':
                opts.input_file = optarg;
                break;
            case 15:
                opts.outside_ornament = true;
                break;
            default:
                std::cerr << "Неизвестный аргумент: " << argv[optind - 1] << std::endl;
                std::exit(1);
        }
    }
    if (opts.input_file.empty()) {
        if (optind == argc - 1) {
            opts.input_file = argv[optind];
        }
    }
    if (opts.output_file.empty()) {
        opts.output_file = "./out.bmp";
    }
    if (opts.output_file == opts.input_file) throw std::runtime_error("Input file equals output file!");
    return opts;
}