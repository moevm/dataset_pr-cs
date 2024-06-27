#include "input.h"
#include "structs.h"

void print_usage()
{
    cout << "Options:\n";
    cout << "  -i, --input <file>         Input file name\n";
    cout << "  -o, --output <file>        Output file name\n";
    cout << "  -r, --rgbfilter            Enable RGB filter\n";
    cout << "  --component_name <name>    Name of RGB component to change\n";
    cout << "  --component_value <value>  Value of RGB component to change\n";
    cout << "  -s, --square               Enable square drawing\n";
    cout << "  --left_up <x,y>            Square left upper corner coordinates\n";
    cout << "  --side_size <size>         Square side size\n";
    cout << "  --thickness <thickness>    Square side thickness\n";
    cout << "  --color <r,g,b>            Square color\n";
    cout << "  --fill	                  Enable/disable square filling\n";
    cout << "  --fill_color <r,g,b>       Square fill color\n";
    cout << "  -e, --exchange             Enable exchange operation\n";
    cout << "  --left_up <x,y>            Exchange left upper corner coordinates\n";
    cout << "  --right_down <x,y>         Exchange right down corner coordinates\n";
    cout << "  --exchange_type <type>     Exchange type (clockwise|counterclockwise|diagonals)\n";
    cout << "  -f, --freq_color           Enable frequent color swaping\n";
    cout << "  --color <r,g,b>            Color to swap\n";
    cout << "  -h, --help                 Show this help message\n";
    cout << "  -I, --info                 Info about this image\n";
}

bool is_integer(const string &str)
{
    if (str.empty())
    {
        return false;
    }
    for (char c : str)
    {
        if (!std::isdigit(c))
        {
            return false;
        }
    }
    return true;
}

Rgb create_Rgb(int b_in, int g_in, int r_in)
{
    if (0 <= b_in <= 255 && 0 <= g_in <= 255 && 0 <= r_in <= 255)
    {
        unsigned char b = (unsigned char)b_in;
        unsigned char g = (unsigned char)g_in;
        unsigned char r = (unsigned char)r_in;
        return Rgb{b, g, r};
    }
    else
    {
        cout << "Error in create_Rgb: some of the arguments are incorrect" << endl;
        exit(45);
    }
}

Config get_config(int argc, char *argv[])
{
    Config config = {"out.bmp"};
    string opts = "i:o:Ihrsef";
    option longOpts[] = {
        {"help", no_argument, NULL, 'h'},
        {"info", no_argument, NULL, 'I'},
        {"input", required_argument, NULL, 'i'},
        {"output", required_argument, NULL, 'o'},
        {"rgbfilter", no_argument, NULL, 'r'},
        {"component_name", required_argument, NULL, 0},
        {"component_value", required_argument, NULL, 0},
        {"square", no_argument, NULL, 's'},
        {"left_up", required_argument, NULL, 0},
        {"side_size", required_argument, NULL, 0},
        {"thickness", required_argument, NULL, 0},
        {"color", required_argument, NULL, 0},
        {"fill", no_argument, NULL, 0},
        {"fill_color", required_argument, NULL, 0},
        {"exchange", no_argument, NULL, 'e'},
        {"left_up", required_argument, NULL, 0},
        {"right_down", required_argument, NULL, 0},
        {"exchange_type", required_argument, NULL, 0},
        {"freq_color", no_argument, NULL, 'f'},
        {"color", required_argument, NULL, 0},
		{"outside_ornament", no_argument, NULL, 0},
        {NULL, 0, NULL, 0}};

    int opt;
    int longIndex;
    opt = getopt_long(argc, argv, opts.c_str(), longOpts, &longIndex);

    while (opt != -1)
    {
        switch (opt)
        {
        case 'i':
            config.name_in_in = 1;
            config.name_in = optarg;
            break;
        case 'o':
            config.name_out_in = 1;
            config.name_out = optarg;
            break;
        case 'r':
            config.rgb_filter = 1;
            break;
        case 's':
            config.square = 1;
            break;
        case 'e':
            config.exchange = 1;
            break;
        case 'f':
            config.frequent = 1;
            break;
        case 'I':
            config.info = 1;
            break;
        case 'h':
            print_usage();
            exit(0);
        case 0:
			if (longOpts[longIndex].name == "outside_ornament")
			{
				config.outside = 1;
			}
            else if (longOpts[longIndex].name == "component_name")
			{
				config.rgb_name_in = 1;
				config.rgb_name = optarg;
			}
			else if (longOpts[longIndex].name == "component_value")
			{
				config.rgb_val_in = 1;
				if (is_integer(optarg))
				{
					config.rgb_val = stoi(optarg);
				}
				else
				{
					cout << "Error in parsing arguments: --component_value argument is incorrect" << endl;
					exit(41);
				}
			}
			else if (longOpts[longIndex].name == "left_up")
			{
				config.sq_lu_in = 1;
				config.ex_lu_in = 1;
				if (is_integer(string(optarg).substr(0, string(optarg).find('.'))) && is_integer(string(optarg).substr(string(optarg).find('.') + 1)))
				{
					int x = stoi(string(optarg).substr(0, string(optarg).find('.')));
					int y = stoi(string(optarg).substr(string(optarg).find('.') + 1));
					config.sq_lu[0] = y;
					config.sq_lu[1] = x;
					config.ex_lu[0] = y;
					config.ex_lu[1] = x;
				}
				else
				{
					cout << "Error in parsing arguments: --left_up argument is incorrect" << endl;
					exit(41);
				}
			}
			else if (longOpts[longIndex].name == "side_size")
			{
				config.sq_side_in = 1;
				if (is_integer(optarg))
				{
					config.sq_side = stoi(optarg);
				}
				else
				{
					cout << "Error in parsing arguments: --side_size argument is incorrect" << endl;
					exit(41);
				}
			}
			else if (longOpts[longIndex].name == "thickness")
			{
				config.sq_thickness_in = 1;
				if (is_integer(optarg))
				{
					config.sq_thickness = stoi(optarg);
					config.outside_thickness = stoi(optarg);
				}
				else
				{
					cout << "Error in parsing arguments: --thickness argument is incorrect" << endl;
					exit(41);
				}
			}
			else if (longOpts[longIndex].name == "color")
			{
				config.sq_color_in = 1;
				config.freq_color_in = 1;
                size_t first_dot = string(optarg).find('.');
				size_t second_dot = string(optarg).find('.', first_dot + 1);
                string r_str = string(optarg).substr(0, first_dot);
                string g_str = string(optarg).substr(first_dot + 1, second_dot - first_dot - 1);
                string b_str = string(optarg).substr(second_dot + 1);
				if (is_integer(r_str) && is_integer(g_str) && is_integer(b_str))
				{
					int r = stoi(r_str);
					int g = stoi(g_str);
					int b = stoi(b_str);
					config.sq_color = create_Rgb(b, g, r);
					config.freq_color = create_Rgb(b, g, r);
					config.outside_color = create_Rgb(b, g, r);
				}
				else
				{
					cout << "Error in parsing arguments: --color argument is incorrect" << endl;
					exit(41);
				}
			}
			else if (longOpts[longIndex].name == "fill")
			{
				config.sq_fill = 1;
			}
			else if (longOpts[longIndex].name == "fill_color")
			{
				config.sq_fill_color_in = 1;
                size_t first_dot = string(optarg).find('.');
				size_t second_dot = string(optarg).find('.', first_dot + 1);
                string r_str = string(optarg).substr(0, first_dot);
                string g_str = string(optarg).substr(first_dot + 1, second_dot - first_dot - 1);
                string b_str = string(optarg).substr(second_dot + 1);
				if (is_integer(r_str) && is_integer(g_str) && is_integer(b_str))
				{
					int r = stoi(r_str);
					int g = stoi(g_str);
					int b = stoi(b_str);
					config.sq_fill_color = create_Rgb(b, g, r);
				}
				else
				{
					cout << "Error in parsing arguments: --fill_color argument is incorrect" << endl;
					exit(41);
				}
			}
			else if (longOpts[longIndex].name == "right_down")
			{
				config.ex_rd_in = 1;
				if (is_integer(string(optarg).substr(0, string(optarg).find('.'))) && is_integer(string(optarg).substr(string(optarg).find('.') + 1)))
				{
					int x = stoi(string(optarg).substr(0, string(optarg).find('.')));
					int y = stoi(string(optarg).substr(string(optarg).find('.') + 1));
					config.ex_rd[0] = y;
					config.ex_rd[1] = x;
				}
				else
				{
					cout << "Error in parsing arguments: --right_down argument is incorrect" << endl;
					exit(41);
				}
			}
			else if (longOpts[longIndex].name == "exchange_type")
			{
				config.ex_type_in = 1;
				config.ex_type = optarg;
			}
			else 
			{
                cout << "Error in parsing arguments: invalid argument '" << optarg << "'" << endl;
                exit(41);
            }
        }
        opt = getopt_long(argc, argv, opts.c_str(), longOpts, &longIndex);
    }

    return config;
}