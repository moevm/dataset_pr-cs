#include "my_lib.h"
#include "collectoprover.h"
#include "bmp_class.h"

int main(int argc, char **argv) {
    cout << "Course work for option 5.3, created by Savelii Borivets" << endl;
    setlocale(LC_ALL, "ru-RU");
    int opt;
    static struct option long_options[] = {
            {"rgbfilter",       no_argument,       0, 'R'},
            {"component_name",  required_argument, 0, 'n'},
            {"component_value", required_argument, 0, 'v'},
            {"square",          no_argument,       0, 'S'},
            {"left_up",         required_argument, 0, 'l'},
            {"side_size",       required_argument, 0, 's'},
            {"thickness",       required_argument, 0, 't'},
            {"color",           required_argument, 0, 'C'},
            {"fill",            no_argument,       0, 'f'},
            {"fill_color",      required_argument, 0, 'c'},
            {"exchange",        no_argument,       0, 'E'},
            {"right_down",      required_argument, 0, 'r'},
            {"exchange_type",   required_argument, 0, 'e'},
            {"freq_color",      no_argument,       0, 'F'},
            {"help",            no_argument,       0, 'h'},
            {"info",            no_argument,       0, 'I'},
            {"input",           required_argument, 0, 'i'},
            {"output",          required_argument, 0, 'o'},
            {"outside_ornament", no_argument, 0, 'O'},
            {0, 0,                                 0, 0}
    };
    map<char, map<string, string>> commander {
            {'R', {
                {"component_name", ""},
                {"component_value", ""}}},
            {'S', {
                {"left_up", ""},
                {"side_size", ""},
                {"thinkness", ""},
                {"color", ""},
                {"fill", ""},
                {"fill_color", ""}}},
            {'E', {
                {"left_up", ""},
                {"right_down", ""},
                {"exchange_type", ""}}},
            {'F', {
                {"color", ""}}},
            {'O', {
                        {"thickness", ""},
                        {"color", ""}}
            }
    };
    string file_name_in;
    string file_name_out;
    char mode;
    //Собиратель данных
    if (argc <= 1) {
        help();
        return 0;
    }
    while ((opt = getopt_long(argc, argv, "Rn:v:Sl:s:t:C:fc:Er:e:FhIi:o:", long_options, nullptr)) != -1) {
        switch (opt) {
            case 'R':
                mode = 'R';
                break;
            case 'n':
                commander['R']["component_name"] = optarg;
                break;
            case 'v':
                commander['R']["component_value"] = optarg;
                break;
            case 'S':
                mode = 'S';
                break;
            case 'l':
                commander['S']["left_up"] = optarg;
                commander['E']["left_up"] = optarg;
                break;
            case 's':
                commander['S']["side_size"] = optarg;
                break;
            case 't':
                commander['S']["thickness"] = optarg;
                commander['O']["thickness"] = optarg;
                break;
            case 'C':
                commander['S']["color"] = optarg;
                commander['F']["color"] = optarg;
                commander['O']["color"] = optarg;
                break;
            case 'f':
                commander['S']["fill"] = "true";
                break;
            case 'c':
                commander['S']["fill_color"] = optarg;
                break;
            case 'E':
                mode = 'E';
                break;
            case 'r':
                commander['E']["right_down"] = optarg;
                break;
            case 'e':
                commander['E']["exchange_type"] = optarg;
                break;
            case 'F':
                mode = 'F';
                break;
            case 'h':
                help();
                return 0;
            case 'I':
                mode = 'I';
                break;
            case 'i':
                file_name_in = optarg;
                break;
            case 'o':
                file_name_out = optarg;
                break;
            case 'O':
                mode = 'O';
                break;
            default:
                cout << "Ошибка: Проблема с флагами или аргументами. Подробнее написано выше" << endl;
                exit(ARG_ERR);
        }
    }
    //Открытие и чтение
    Bitmap BM;
    if (file_name_in.empty()) {
        cout << "Ошибка: Имя файла не было введено." << endl;
        exit(ARG_ERR);
    }
    BM.read_bmp(file_name_in);
    //Работа с файлом
    switch (mode) {
        case 'R':{
            string component_name = component_name_prove(commander[mode]["component_name"]);
            unsigned char component_value = color_value_prove(commander[mode]["component_value"]);
            BM.rgbfilter(component_name, component_value);
            break;}
        case 'S':{
            vector<int> coordinates = coord_prove(commander[mode]["left_up"], BM.get_height());
            int left = coordinates[0], up = coordinates[1];
            int side_size = int_prove(commander[mode]["side_size"], "Сторона квадрата");
            int thickness = int_prove(commander[mode]["thickness"], "Толщина стороны квадрата");
            Rgb color = color_prove(commander[mode]["color"]);
            bool fill = false;
            Rgb fill_color;
            if (commander['S']["fill"] == "true") {
                fill = true;
                fill_color = color_prove(commander[mode]["fill_color"]);
            }
            BM.square(left, up, side_size, thickness, color, fill, fill_color);
            break;}
        case 'E':{
            vector<int> coordinates1 = coord_prove(commander[mode]["left_up"], BM.get_height());
            vector<int> coordinates2 = coord_prove(commander[mode]["right_down"], BM.get_height());
            int left = coordinates1[0], up = coordinates1[1], right = coordinates2[0], down = coordinates2[1];
            BM.exchange(left, up, right, down, exchange_type_prove(commander[mode]["exchange_type"]));
            break;}
        case 'F':{
            Rgb color = color_prove(commander[mode]["color"]);
            BM.freq_color(color);
            break;}
        case 'I':
            BM.print_file_header();
            BM.print_info_header();
            return 0;
        case 'O':
            BM.outside_ornament(int_prove(commander[mode]["thickness"], "Толщина стороны квадрата"), color_prove(commander[mode]["color"]));
            break;
    }
    //Запись измененного файла
    if (file_name_out.empty()) {
        file_name_out = "out.bmp";
    }
    BM.write_bmp(file_name_out);
    return 0;
}