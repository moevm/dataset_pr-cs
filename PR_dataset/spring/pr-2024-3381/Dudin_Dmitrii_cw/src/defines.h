#pragma once

#define HELP "Course work for option 4.7, created by Dmitrii Dudin.\n(1) Рисование треугольника. Флаг для выполнения данной операции: `--triangle`. Треугольник определяется\nКоординатами его вершин. Флаг `--points`, значение задаётся в формате `x1.y1.x2.y2.x3.y3` (точки будут (x1; y1), (x2; y2) и (x3; y3)), где x1/x2/x3 – координаты по x, y1/y2/y3 – координаты по y\nТолщиной линий. Флаг `--thickness`. На вход принимает число больше 0\nЦветом линий. Флаг `--color` (цвет задаётся строкой `rrr.ggg.bbb`, где rrr/ggg/bbb – числа, задающие цветовую компоненту. пример `--color 255.0.0` задаёт красный цвет)\nТреугольник может быть залит или нет. Флаг `--fill`. Работает как бинарное значение: флага нет – false , флаг есть – true.\nцветом которым он залит, если пользователем выбран залитый. Флаг `--fill_color` (работает аналогично флагу `--color`)\n(2) Находит самый большой прямоугольник заданного цвета и перекрашивает его в другой цвет. Флаг для выполнения данной операции: `--biggest_rect`. Функционал определяется:\nЦветом, прямоугольник которого надо найти. Флаг `--old_color` (цвет задаётся строкой `rrr.ggg.bbb`, где rrr/ggg/bbb – числа, задающие цветовую компоненту. пример `--old_color 255.0.0` задаёт красный цвет)\nЦветом, в который надо его перекрасить. Флаг `--new_color` (работает аналогично флагу `--old_color`)\n(3) Создать коллаж размера N*M из одного изображения. Флаг для выполнения данной операции: `--collage`. Коллаж представляет собой это же самое изображение повторяющееся N*M раз.\nКоличество изображений по “оси” Y.  Флаг `--number_y`. На вход принимает число больше 0\nКоличество изображений по “оси” X.  Флаг `--number_x`. На вход принимает число больше 0\n"
#define OK_CODE 0
#define NONE_VALUE -1

#define EXIT_CODE 42
#define ERROR_TEMPLATE "%s. Exit code: %d\n"

#define ALLOC_ERROR "Error: allocate of memory"

#define NO_ARG_VAL_ERROR "Error: argument required value"
#define UNKNOWN_ARG_ERROR "Error: unknown argument"
#define NO_INPUT_FILE_ARG_ERROR "Error: not geted input-file"

#define REGCOMP_ERROR "Error: The regular expression could not be completed"

#define SELECTED_FUNCTIONS_COUNT_ERROR "Error: selected funtions count not equal 1"
#define ARG_VAL_ERROR "Error: argument(s) value is not correct"

#define NO_FILE_ERROR "Error: file not found"
#define INVALID_FILE_ERROR "Error: invalid file format"
#define OUTPUT_FILE_ERROR "Error: cant create output file"

#define DEFAULT_OUTPUT_BMP "out.bmp"

#define LONG_OPT_FLAG 0
#define NO_ARG_VAL ':'
#define UNKNOWN_ARG '?'

#define SHORT_INPUT_ARG 'i'
#define SHORT_OUTPUT_ARG 'o'
#define SHORT_HELP_ARG 'h'
#define SHORT_OPTIONS "i:o:h"

#define INPUT_ARG "input"
#define OUTPUT_ARG "output"
#define HELP_ARG "help"
#define INFO_ARG "info"
#define COLOR_ARG "color"
#define TRIANGLE_ARG "triangle"
#define BIGGEST_RECT_ARG "biggest_rect"
#define COLLAGE_ARG "collage"
#define FILL_ARG "fill"
#define NUMBER_Y_ARG "number_y"
#define NUMBER_X_ARG "number_x"
#define THICKNESS_ARG "thickness"
#define POINTS_ARG "points"
#define OLD_COLOR_ARG "old_color"
#define NEW_COLOR_ARG "new_color"
#define FILL_COLOR_ARG "fill_color"


#define REGEX_NATURAL_NUM "^[1-9][0-9]*$"
#define REGEX_COORDINATES "^([-]?[0-9]+)\\.([-]?[0-9]+)$"
#define REGEX_TRIANGLE_POINTS "^([-]?[0-9]+)\\.([-]?[0-9]+)\\.([-]?[0-9]+)\\.([-]?[0-9]+)\\.([-]?[0-9]+)\\.([-]?[0-9]+)$"
#define REGEX_COLOR "^([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\\.([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\\.([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$"
#define MAX_CAPTURE_GROUP 7


#define SIGNATRUE 19778
#define BMP_PIX_SIZE 24