#include "my_lib.h"

int int_prove(string value, string place) {
    if (value.size() == 0) {
        cout << "Ошибка: Не было введено - " << place << endl;
        exit(NO_ARG_ERR);
    }
    bool flag = false;
    string err_sym = "";
    string new_value = "";
    for (int i = 0; i < value.size(); i++) {
        if (!isdigit(value[i])) {
            if (strchr(err_sym.c_str(), value[i]) == NULL) err_sym += value[i];
            flag = true;
        } else {
            new_value += value[i];
        }
    }
    if (flag) {
        cout << "Возможная ошибка устранена: Лишние символы [" << err_sym << "] в значении - " << place << endl;
    }
    return stoi(new_value);
}

unsigned char color_value_prove(string value) {
    int pix_val = int_prove(value, "Значение цвета пикселя");
    if (0 <= pix_val && pix_val <= 255) return pix_val;
    cout << "Ошибка: Значение цвета пикселя должно быть в диапазоне от 0 до 255. Было введено значение - " << pix_val << endl;
    exit(ARG_ERR);
}

Rgb color_prove(string color) {
    if (color.size() == 0) {
        cout << "Ошибка: Значение цвета не было введено" << endl;
        exit(NO_ARG_ERR);
    }
    Rgb new_color;
    color += '.';
    string color_val = "";
    int mode = 0; //0 - red, 1 - green, 2 - blue
    for (int i = 0; i < color.size(); i++) {
        if (isdigit(color[i])) {
            color_val += color[i];
        } else if (color[i] == '.') {
            switch (mode) {
                case 0:
                    new_color.r = color_value_prove(color_val);
                    break;
                case 1:
                    new_color.g = color_value_prove(color_val);
                    break;
                case 2:
                    new_color.b = color_value_prove(color_val);
                    return new_color;
            }
            color_val = "";
            mode++;
        }
    }
    cout << "Ошибка: Недостаточно аргументов цвета пикселей" << endl;
    exit(NO_ARG_ERR);
}

string component_name_prove(string comp) {
    for (int i = 0; i < comp.size(); i++) {
        comp[i] = tolower(comp[i]);
    }
    if (comp == "red" || comp == "green" || comp == "blue") {
        return comp;
    }
    cout << "Ошибка: Некорректный цвет - " << comp << endl;
    exit(ARG_ERR);
}

vector<int> coord_prove(string coord, int H) {
    coord += '.';
    vector<int> v_coord(2);
    int cnt = 0;
    string coordinate;
    for (int i = 0; i < coord.size(); i++) {
        if (isdigit(coord[i])) {
            coordinate += coord[i];
        } else if (coord[i] == '.') {
            v_coord[cnt] = int_prove(coordinate, "Значение координат.");
            cnt++;
            coordinate = "";
        }
        if (cnt == 2) {
            //Переворот второй координаты
            v_coord[1] = H - 1 - v_coord[1];
            return v_coord;
        }
    }
    cout << "Ошибка: Нет или не хватает значений координат.";
    exit(NO_ARG_ERR);
}

char exchange_type_prove(string exchange_type) {
    if (!exchange_type.size()) {
        cout << "Ошибка: Не введен способ обмена частей" << endl;
        exit(NO_ARG_ERR);
    }
    for (int i = 0; i < exchange_type.size(); i++) {
        exchange_type[i] = tolower(exchange_type[i]);
    }
    if (exchange_type == "clockwise" || exchange_type == "counterclockwise" || exchange_type == "diagonals") {
        return exchange_type[1];
    }
    cout << "Ошибка: Некорректный способ обмена частей - " << exchange_type << endl;
    exit(ARG_ERR);
}

#define RESET "\x1B[0m" //Обычный вывод в консоль
#define MAIN_TEXT "\x1B[1;4;36m" //Главный заголовок
#define SECOND_TEXT "\x1B[1;34m" //Заголовки
#define FLAG_COLOR "\x1B[1;32m" //Флаги
#define DESCRIPTION "\x1B[1;35m" //Описание функций

void help() {
    cout << MAIN_TEXT << "ВАС ПРИВЕТСТВУЕТ СПРАВОЧНИК, КОТОРЫЙ РАССКАЖЕТ О РАБОТЕ ПРОГРАММЫ" << RESET << endl << endl;

    cout << MAIN_TEXT << "ФЛАГИ СПРАВКИ, ВВОДА, ВЫВОДА, ДОПОЛНИТЕЛЬНОЙ ИНФОРМАЦИИ" << RESET <<  endl << endl;

    cout << FLAG_COLOR << "--help/-h" << RESET;
    cout << DESCRIPTION << " - вызов справочника. Все остальные введённые аргументы будут проигнорированы." << RESET << endl;
    cout << FLAG_COLOR << "--input/-i" << RESET;
    cout << DESCRIPTION << " - название входного файла формата BMP. Если файла с таким названием не существует - будет выведена ошибка." << RESET << endl;
    cout << FLAG_COLOR << "--output/-o" << RESET;
    cout << DESCRIPTION << " - название выходного файла формата BMP. Если флаг отсутствует, файл будет назван out.bmp." << RESET << endl;
    cout << FLAG_COLOR << "--info/-I" << RESET;
    cout << DESCRIPTION << " - вывод подробной информации о введённом BMP файле." << RESET << endl << endl;

    cout << MAIN_TEXT << "ФЛАГИ ДЛЯ ИЗМЕНЕНИЯ ИЗОБРАЖЕНИЯ" << RESET <<  endl << endl;

    cout << FLAG_COLOR << "--rgbfilter/-R" << RESET;
    cout << DESCRIPTION << " - фильтр rgb-компонент. Устанавливает значение заданной компоненты в диапазоне от 0 до 255 для всего изображения." << RESET << endl;
    cout << SECOND_TEXT << "Обязательные флаги:" << RESET << endl;
    cout << FLAG_COLOR << "--component_name/-n" << RESET;
    cout << DESCRIPTION << " - компонента, которую необходимо изменить. Возможные значения: 'red', 'green', 'blue'." << RESET << endl;
    cout << FLAG_COLOR << "--component_value/-v" << RESET;
    cout << DESCRIPTION << " - значение компоненты в диапазоне от 0 до 255." << RESET << endl << endl;

    cout << FLAG_COLOR << "--square/-S" << RESET;
    cout << DESCRIPTION << " - рисование квадрата по заданным координатам левого верхнего угла, размером стороны, толщине и цвету линий. Также можно выполнить заливку внутренней области квадрата." << RESET << endl;
    cout << SECOND_TEXT << "Обязательные флаги:" << RESET << endl;
    cout << FLAG_COLOR << "--left_up/-l" << RESET;
    cout << DESCRIPTION << " - координаты левого верхнего угла квадрата в формате 'left.up', где left - координата по x, up - координата по y." << RESET << endl;
    cout << FLAG_COLOR << "--side_size/-s" << RESET;
    cout << DESCRIPTION << " - размер стороны квадрата. Принимается значение больше 0. Отрицательные значения становятся положительными." << RESET << endl;
    cout << FLAG_COLOR << "--thickness/-t" << RESET;
    cout << DESCRIPTION << " - толщина линий квадрата. Принимается значение больше 0. Отрицательные значения становятся положительными." << RESET << endl;
    cout << FLAG_COLOR << "--color/-C" << RESET;
    cout << DESCRIPTION << " - цвет границ квадрата. Цвет задается строкой 'red.green.blue' - значения от 0 до 255 через точку." << RESET << endl;
    cout << SECOND_TEXT << "Дополнительные флаги:" << RESET << endl;
    cout << FLAG_COLOR << "--fill/-f" << RESET;
    cout << DESCRIPTION << " - флаг заливки. При его присутствии выполняется заливка." << RESET << endl;
    cout << FLAG_COLOR << "--fill_color/-c" << RESET;
    cout << DESCRIPTION << " - цвет заливки. вет задается строкой 'red.green.blue' - значения от 0 до 255 через точку. Если флаг --fill/-f отсутствует - заливка не выполняется." << RESET << endl << endl;

    cout << FLAG_COLOR << "--exchange/-E" << RESET;
    cout << DESCRIPTION << " - смена 4 фрагментов области." << RESET << endl;
    cout << SECOND_TEXT << "Обязательные флаги:" << RESET << endl;
    cout << FLAG_COLOR << "--left_up/-l" << RESET;
    cout << DESCRIPTION << " - координаты левого верхнего угла области в формате 'left.up', где left - координата по x, up - координата по y." << RESET << endl;
    cout << FLAG_COLOR << "--right_down/-r" << RESET;
    cout << DESCRIPTION << " - координаты правого нижнего угла области в формате 'right.down', где right - координата по x, down - координата по y." << RESET << endl;
    cout << FLAG_COLOR << "--exchange_type/-e" << RESET;
    cout << DESCRIPTION << " - способы обмена частей. Возможные варианты: clockwise(по часовой), counterclockwise(против часовой), diagonals(по диагонали)" << RESET << endl << endl;

    cout << FLAG_COLOR << "--freq_color/-F" << RESET;
    cout << DESCRIPTION << " - находит самый часто встречаемый цвет и заменяет его на другой заданный цвет." << RESET << endl;
    cout << SECOND_TEXT << "Обязательные флаги:" << RESET << endl;
    cout << FLAG_COLOR << "--color/-C" << RESET;
    cout << DESCRIPTION << " - новый цвет. Цвет задается строкой 'red.green.blue' - значения от 0 до 255 через точку." << RESET << endl << endl;
}