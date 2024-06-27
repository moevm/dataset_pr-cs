#include "../include/functions.h"

void print_info(PICInfo& info, const string& file_name){
    cout << "File name: " << file_name << endl;
    cout << "File type: " << info.header.Type[0] << info.header.Type[1] << endl;
    cout << "Height: " << info.header.Height << endl;
    cout << "Width: " << info.header.Width << endl;
    cout << "Size: " << info.header.Size << " bytes" << endl;
    cout << "Color depth: " << info.header.BitCount << endl;
    exit(0);
}

int* get_colors(string& colors){
    istringstream stream_colors(colors);
    int* arr_colors = new int[3];
    char dot1, dot2;

    try{
        if (!(stream_colors >> arr_colors[0] >> dot1 >> arr_colors[1] >> dot2 >> arr_colors[2]) or dot1 != '.' or dot2 != '.') {
            throw 1;
        }
        for (int i = 0; i < 3; ++i) {
            if (arr_colors[i] < 0 or arr_colors[i] > 255) {
                throw 1;
            }
        }
    }catch (int e){
        cerr << "Colors entered incorrectly: " << colors << endl;
        exit(40);
    }

    return arr_colors;
}

void cli_parse(int argc, char* argv[]){
    int opt;
    PICInfo info{};
    OptionTools tools{};
    deque<function<void()>> operations;
    vector<char> used_flags;
    string output_file_name = "out.bmp";
    string input_file_name;
    string current_func;

    while((opt = getopt_long(argc, argv, "i:o:hrnf", long_flags, nullptr)) != -1){
        switch(opt){
            case 'h': {
                cout << HELP_INFO << endl;
                exit(0);
            }
            case 'i': {
                input_file_name = optarg;
                break;
            }
            case 'o': {
                output_file_name = optarg;
                break;
            }
            case 256: {
                auto get_info = [&input_file_name, &info] {print_info(info, input_file_name);};
                operations.emplace_back(get_info);
                break;
            }
            case 'r': {
                used_flags.push_back('r');
                break;
            }
            case 257: {
                string s_old_colors = optarg;
                tools.old_color = get_colors(s_old_colors);
                break;
            }
            case 258: {
                string s_new_colors = optarg;
                tools.new_color = get_colors(s_new_colors);
                break;
            }
            case 'n': {
                used_flags.push_back('n');
                current_func = "ornament";
                break;
            }
            case 259: {
                tools.pattern = optarg;
                break;
            }
            case 260: {
                string s_colors = optarg;
                if(current_func == "ornament"){
                    tools.pattern_color = get_colors(s_colors);
                } else if (current_func == "find_rects"){
                    tools.rect_color = get_colors(s_colors);
                } else {
                    for (int i = 0; i < argc; ++i) {
                        if(strcmp(argv[i], "--ornament") == 0){
                            tools.pattern_color = get_colors(s_colors);
                        }
                        if(strcmp(argv[i], "--filled_rects") == 0){
                            tools.rect_color = get_colors(s_colors);
                        }
                    }
                }
                break;
            }
            case 261: {
                try {
                    int value = stoi(optarg);
                    if(current_func == "ornament"){
                        tools.pattern_thickness = value;
                        if(tools.pattern_thickness < 1){
                            throw invalid_argument("thickness less than 1");
                        }
                    } else if (current_func == "find_rects"){
                        tools.border_thickness = value;
                        if(tools.border_thickness < 1){
                            throw invalid_argument("thickness less than 1");
                        }
                    } else {
                        for (int i = 0; i < argc; ++i) {
                            if(strcmp(argv[i], "--ornament") == 0){
                                tools.pattern_thickness = value;
                            }
                            if(strcmp(argv[i], "--filled_rects") == 0){
                                tools.border_thickness = value;
                            }
                        }
                    }
                } catch (invalid_argument& e) {
                    cerr << "Invalid argument for thickness parameter" << endl;
                    exit(40);
                }
                break;
            }
            case 262: {
                try {
                    tools.count = stoi(optarg);
                    if(tools.count < 1){
                        throw invalid_argument("count less than 1");
                    }
                } catch (invalid_argument& e) {
                    cerr << "Invalid argument for count parameter" << endl;
                    exit(40);
                }
                break;
            }
            case 'f': {
                used_flags.push_back('f');
                current_func = "find_rects";
                break;
            }
            case 263: {
                string s_border_colors = optarg;
                int* color = get_colors(s_border_colors);
                tools.border_color = color;
                break;
            }
            case 'w': {
                used_flags.push_back('w');
                break;
            }
            default:
                cerr << "Unknown flag" << endl;
                exit(40);
        }
    }
    if(input_file_name.empty()){
        input_file_name = argv[argc - 1];
    }

    if(input_file_name == output_file_name){
        cerr << "The names of the input and output files are the same" << endl;
        exit(40);
    }

    auto read_file = [input_file_name, &info] {info = read(input_file_name);};
    operations.emplace_front(read_file);

    for(char flag : used_flags) {
        if (flag == 'r') {
            auto replace = [&info, &tools] {
                color_replace(info, tools.old_color, tools.new_color);
            };
            operations.emplace_back(replace);
        }
        if (flag == 'f') {
            auto find = [&info, &tools] {
                find_rectangle(info, tools.rect_color, tools.border_thickness, tools.border_color);
            };
            operations.emplace_back(find);
        }
        if (flag == 'n') {
            auto frame = [&info, &tools] {
                ornament(info, tools.pattern, tools.pattern_color, tools.pattern_thickness, tools.count);
            };
            operations.emplace_back(frame);
        }
        if (flag == 'w'){
            auto hsv_f = [&info] {
                hsv(info);
            };
            operations.emplace_back(hsv_f);
        }
    }

    auto write_file = [output_file_name, &info] { write(info, output_file_name);};
    operations.emplace_back(write_file);


    while(!operations.empty()){
        operations.front()();
        operations.pop_front();
    }

    delete tools.old_color;
    delete tools.new_color;
    delete tools.pattern_color;
    delete tools.rect_color;
    delete tools.border_color;
}
