#include "command.h"
#include <getopt.h>
#include "mirror.h"
#include "draw.h"
#include "portable_network_graphic.h"
#include <iostream>
#include <sstream>
#include "struct_png.h"
#include <cstring>
#include <png.h>
//#include "/opt/homebrew/include/png.h"

using namespace std;

void help(){
    cout << "Course work for option 5.15, created by Kantserov Artemii." << endl;
    std::cout << "Использование: png_processor [ОПЦИИ]" << std::endl;
    std::cout << "Опции:" << std::endl;
    std::cout << "  --input, -i <файл>         Входной PNG файл" << std::endl;
    std::cout << "  --output, -o <файл>        Выходной PNG файл (по умолчанию: out.png)" << std::endl;
    std::cout << "  --mirror, -m               Зеркальное отражение изображения" << std::endl;
    std::cout << "  --axis, -a <x|y>           Ось для зеркального отражения (x - горизонтальная, y - вертикальная)" << std::endl;
    std::cout << "  --left_up, -u <x.y>        Координаты верхнего левого угла области (например: --left_up 10.20)" << std::endl;
    std::cout << "  --right_down, -d <x.y>     Координаты нижнего правого угла области (например: --right_down 100.200)" << std::endl;
    std::cout << "  --pentagram, -p            Рисование пентаграммы" << std::endl;
    std::cout << "  --center, -C <x.y>         Координаты центра фигуры (например: --center 50.50)" << std::endl;
    std::cout << "  --radius, -R <значение>    Радиус фигуры (например: --radius 30)" << std::endl;
    std::cout << "  --thickness, -t <значение> Толщина линий (например: --thickness 3)" << std::endl;
    std::cout << "  --color, -c <r.g.b>        Цвет линий (например: --color 255.0.0 для красного цвета)" << std::endl;
    std::cout << "  --rect, -r                 Рисование прямоугольника" << std::endl;
    std::cout << "  --fill, -f                 Заливка фигуры (только для прямоугольника и шестиугольника)" << std::endl;
    std::cout << "  --fill_color, -F <r.g.b>   Цвет заливки (например: --fill_color 0.255.0 для зеленого цвета)" << std::endl;
    std::cout << "  --hexagon, -H              Рисование шестиугольника" << std::endl;
    std::cout << "  --help, -h                 Показать это сообщение и выйти" << std::endl;
    std::cout << "  --info, -I                 Показать информацию об изображении и выйти" << std::endl;
    std::cout << std::endl;
    std::cout << "Примеры использования:" << std::endl;
    std::cout << "  png_processor -i input.png -o output.png --mirror -a x -u 10.20 -d 100.200" << std::endl;
    std::cout << "  png_processor -i input.png --pentagram -C 50.50 -r 30 -t 3 -c 255.0.0" << std::endl;
    std::cout << "  png_processor -i input.png --rect -l 10.20 -C 100.200 -t 3 -c 0.0.255 --fill -F 255.255.0" << std::endl;
    std::cout << "  png_processor -i input.png --hexagon -C 50.50 -r 30 -t 3 -c 0.255.0 --fill -F 0.0.255" << std::endl;
    std::cout << std::endl;
}


int process_args(int argc, char* argv[], struct Png* image) {
    bool l_u = false, r_d = false, C = false, t = false, r = false;
    int cor1[2] = {-1, -1}, cor2[2] = {-1, -1}, center[2] = {-1, -1};
    int color[3] = {-1, -1, -1}, color_fill[3] = {-1, -1, -1};
    int thickness = 0, radius = 0, func = 0;
    char axis = 'r';
    bool fill = false;
    string file_input_name = argv[argc-1];
    string file_output_name = "out.png";
    const char optString[] = "d:u:HrmpC:hc:t:c:a:R:F:fIi:o:";
    int opt;
    struct option options[] = {
            {"hexagon",    no_argument, nullptr, 'H'},
            {"rect",       no_argument, nullptr, 'r'},
            {"pentagram",  no_argument, nullptr, 'p'},
            {"mirror",     no_argument, nullptr, 'm'},
            {"help",       no_argument, nullptr, 'h'},
            {"color",      required_argument, nullptr, 'c'},
            {"thickness",  required_argument, nullptr, 't'},
            {"center",     required_argument, nullptr, 'C'},
            {"axis",       required_argument, nullptr, 'a'},
            {"radius",     required_argument, nullptr, 'R'},
            {"fill",       no_argument, nullptr, 'f'},
            {"fill_color", required_argument, nullptr, 'F'},
            {"left_up",    required_argument, nullptr, 'u'},
            {"right_down", required_argument, nullptr, 'd'},
            {"info",       no_argument, nullptr, 'I'},
            {"input",      required_argument, nullptr, 'i'},
            {"output",     required_argument, nullptr, 'o'},
            {nullptr, 0,                      nullptr, 0}
    };
    while ((opt = getopt_long(argc, argv, optString, options, nullptr)) != -1) {
        char c;
        switch (opt) {
            case 'I':
                func = 5;
                break;
            case 'h':
                help();
                return 0;
            case 'r':
                func = 3;
                break;
            case 'p':
                func = 2;
                break;
            case 'm':
                func = 1;
                break;
            case 'H':
                func = 4;
                break;
            case 'o':
                file_output_name = optarg;
                break;
            case 'i':
                file_input_name = optarg;
                break;
            case 'u': {
                stringstream uu(optarg);
                if (uu >> cor1[0] >> c >> cor1[1] && c == '.') {
                    l_u = true;
                } else {
                    cerr << "Ошибка при разборе координат left_up" << endl;
                    return 45;
                }
                break;
            }
            case 'd': {
                stringstream dd(optarg);
                if (dd >> cor2[0] >> c >> cor2[1] && c == '.') {
                    r_d = true;
                } else {
                    cerr << "Ошибка при разборе координат right_down" << endl;
                    return 45;
                }
                break;
            }
            case 'C': {
                stringstream CC(optarg);
                if (CC >> center[0] >> c >> center[1] && c == '.') {
                    C = true;
                } else {
                    cerr << "Ошибка при разборе координат center" << endl;
                    return 45;
                }
                break;
            }
            case 't': {
                size_t i;
                for (i = 0; i < strlen(optarg); i++) {
                    if (!isdigit(optarg[i])) {
                        cout << "Неверный формат ввода для thickness" << endl;
                        return 45;
                    }
                }
                thickness = stoi(optarg);
                if (thickness < 1) {
                    cout << "Толщина должна быть больше 0" << endl;
                    return 45;
                } else {
                    t = true;
                }
                break;
            }
            case 'c': {
                stringstream ss(optarg);
                char sep;
                if (ss >> color[0] >> sep >> color[1] >> sep >> color[2] && sep == '.') {
                } else {
                    return 45;
                }
                break;
            }
            case 'f':
                fill = true;
                break;
            case 'F': {
                stringstream ss(optarg);
                char sep;
                if (ss >> color_fill[0] >> sep >> color_fill[1] >> sep >> color_fill[2] && sep == '.') {
                } else {
                    return 45;
                }
                break;
            }
            case 'R': {
                size_t i;
                for (i = 0; i < strlen(optarg); i++) {
                    if (!isdigit(optarg[i])) {
                        cout << "Неверный формат ввода для radius" << endl;
                        return 45;
                    }
                }
                radius = stoi(optarg);
                if (radius < 1) {
                    cout << "Радиус должен быть больше 0" << endl;
                    return 45;
                } else {
                    r = true;
                }
                break;
            }
            case 'a':
                axis = optarg[0];
                break;
            default:
                cout << "Неизвестная опция: " << argv[optind - 1] << endl;
                return 45;
        }
    }
    const char* f_i_n = file_input_name.c_str();
    int a = read_png_file(f_i_n, image);
    if (a) {
        return 45;
    }
    if (png_get_color_type(image->png_ptr, image->info_ptr) == PNG_COLOR_TYPE_RGBA){
        return 45;
    }
    switch (func) {
        case 1:
            if (axis != 'x' && axis != 'y') {
                cout << "Invalid axis input, expected 'x' or 'y'." << endl;
                return 45;
            }
            if (!l_u) {
                cout << "The coordinates of the upper left corner were not entered." << endl;
                return 45;
            }
            if (!r_d) {
                cout << "The coordinates of the lower right corner were not entered." << endl;
                return 45;
            }
            mirror(image, axis, cor1, cor2);
            break;
        case 2:
            if (!C) {
                cout << "Center coordinates were not entered." << endl;
                return 45;
            }
            if (!r) {
                cout << "The line thickness was not entered." << endl;
                return 45;
            }
            if (!t) {
                return 45;
            }
            if (!color[1]) {
                return 45;
            }
            pentagram(image, center, radius, thickness, color);
            break;
        case 3:
            if (!l_u) {
                return 45;
            }
            if (!r_d) {
                return 45;
            }
            if (!t) {
                return 45;
            }
            if (color[1] == -1) {
                return 45;
            }
            if (fill) {
                if (color_fill[0] == -1) {
                    return 45;
                }
            }
            rect(image, cor1, cor2, thickness, color, fill, color_fill);
            break;
        case 4:
            if (!C) {
                return 45;
            }
            if (!r) {
                return 45;
            }
            if (!t) {
                return 45;
            }
            if (color[1] == -1) {
                return 45;
            }
            if (fill) {
                if (color_fill[0] == -1) {
                    return 45;
                }
            }
            hexagon(image, center, radius, thickness, color, fill, color_fill);
            break;
        case 5:
            info(image);
        default:
            return 45;

    }
    const char* f_o_n = file_output_name.c_str();
    a = write_png_file(f_o_n, image);
    if (a) {
        return 45;
    }
    return 0;
}