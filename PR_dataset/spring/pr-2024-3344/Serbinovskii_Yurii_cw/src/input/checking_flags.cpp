#include "checking_flags.h"

struct option long_opt[]={
    {"input", 1, 0, 'i'},
    {"output", 1, 0, 'o'},
    {"info", 0, 0, 0},
    {"help", 0, 0, 'h'},
    {"rect", 0, 0, 0},
    {"left_up", 1, 0, 0},
    {"right_down", 1, 0, 0},
    {"thickness", 1, 0, 0},
    {"color", 1, 0, 0},
    {"fill_color", 1, 0, 0},
    {"ornament", 0, 0, 0},
    {"pattern", 1, 0, 0},
    {"color", 1, 0, 0},
    {"count", 1, 0, 0},
    {"rotate", 0, 0, 0},
    {"angle", 1, 0, 0},
    {"circle", 0, 0, 0},
    {"center", 1, 0, 0},
    {"radius", 1, 0, 0},
    {"fill", 2, 0, 0},
    {"outside_ornament", 0, 0, 0},
    {0, 0, 0, 0}
};


std::unordered_map<std::string, std::string> getFlags(int argc, char** argv) 
{
    int optindx;
    int opt;
    opterr = 0;
    std::string flag;
    std::unordered_map<std::string, std::string> flags_table;

    while((opt = getopt_long(argc, argv, "i:o:h", long_opt, &optindx)) != -1) {
        switch (opt)
        {
        case '?':
            std::cerr << UNKNOWN_ARG << argv[optind - 1] << std::endl;
            std::cout << HELP << std::endl;
            exit(44);
            break;
        case 'i':
            flags_table["input"] = optarg;
            break;
        case 'o':
            flags_table["output"] = optarg;
            break;
        case 'h':
            flags_table["help"] = "";
            break;
        default:
            if (flags_table.find("input") == flags_table.end()) {
                if (optind < argc) 
                {
                    flags_table["input"] = argv[argc - 1];
                } 
                else 
                {
                    std::cerr << INPUT << std::endl;
                    exit(43);
                }
            }
            if (optarg) {
                flags_table[long_opt[optindx].name] = optarg;
            }
            else {
                flags_table[long_opt[optindx].name] = "";
            }
            break;
        }
    }
    return flags_table;
}
