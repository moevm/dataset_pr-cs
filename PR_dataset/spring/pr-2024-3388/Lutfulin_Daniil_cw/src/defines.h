#pragma once

#define STR_END '\0'

#define NO_ARGUMENT_VALUE ':'
#define UNKNOWN_ARGUMENT '?'
#define SHORT_HELP_ARG 'h'
#define SHORT_INPUT_ARG 'i'
#define SHORT_OUTPUT_ARG 'o'
#define SHORT_MIRROR_ARG 'm'
#define SHORT_COPY_ARG 'c'
#define SHORT_COLOR_REPLACE_ARG 'r'
#define SHORT_SPLIT_ARG 's'
#define SHORT_OPTSTRING "hi:o:mcrs"

#define LONG_OPT_ARG 0
#define HELP_ARG "help"
#define INFO_ARG "info"
#define INPUT_ARG "input"
#define OUTPUT_ARG "output"
#define MIRROR_ARG "mirror"
#define AXIS_ARG "axis"
#define LEFT_UP_ARG "left_up"
#define LEFT_UP_ARG "left_up"
#define RIGHT_DOWN_ARG "right_down"
#define COPY_ARG "copy"
#define DEST_LEFT_UP_ARG "dest_left_up"
#define COLOR_REPLACE_ARG "color_replace"
#define OLD_COLOR_ARG "old_color"
#define NEW_COLOR_ARG "new_color"
#define SPLIT_ARG "split"
#define NUMBER_X_ARG "number_x"
#define NUMBER_Y_ARG "number_y"
#define THICKNESS_ARG "thickness"
#define COLOR_ARG "color"
#define BINARIZATION_ARG "binarization"
#define TRASH_HOLD_ARG "threshold"
#define ORNAMET_ARG "outside_ornament"
#define DEFAULT_OUTPUT_FILE "out.bmp"
#define HELP_TEXT_LEN 5000
#define HELP_FILENAME "./help.txt"

#define NO_ARGUMENT_VALUE_ERROR "Error: argument does not have requiered value\n"
#define SAME_FILENAME_ERROR "Error: input file name is same to output file name\n"
#define UNKNOWN_ARGUMENT_ERROR "Error: unknown argument\n"
#define ARGUMENT_FORMAT_ERROR "Error: false argument format\n"
#define MAIN_ARGS_NUMBER_ERROR "Error: too many main arguments chosen. Choose only one from --mirror, --copy, --color_replace, --split, --info\n"
#define NOT_ALL_ARGUMENTS_ERROR "Error: not enough arguments\n"
#define NO_FILE_ERROR_TEMPLATE "Error: couldn't open file: "
#define ARGUMENT_ERROR_CODE 40

#define REGEX_COMPILE_ERROR "Error: can't compile regex"
#define REGEX_COORDS "^(0+|-?[1-9][0-9]*)\\.(0+|-?[1-9][0-9]*)$"
#define REGEX_COORDS_GROUPS 3
#define REGEX_COLOR "^([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\\.([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\\.([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$"
#define REGEX_COLOR_GROUPS 4
#define REGEX_ERROR_CODE 41

#define BMP_SIGNATURE 0x4D42
#define SIGNATURE_ERROR "Error: false file signature\n"
#define BITS_PER_PIXEL 24
#define BITS_PER_PIXEL_ERROR "Error: there should be 24 bits per pixel\n"
#define WRONG_FILENAME_ERROR "Error: file name is not BMP\n"
#define NOT_INFO_HEADER_ERROR "Error: type of BITMAPINFO is not BITMAPINFOHEADER\n"
#define IMAGE_ERROR_CODE 42
#define HELP_TEXT "Course work for option 5.2, created by Daniil Lutfulin.\nПрограмма имеет 4 функции по обработке изображения.\n\tОтражение заданной области. Флаг для выполнения данной операции: `--mirror`. Функционал определяется:\nВыбором оси. Флаг `--axis`, возможные значения `x` и `y`\nКоординатами левого верхнего угла области. Флаг `--left_up`, значение задаётся в формате `left.up`, где left – координата по x, up – координата по y\nКоординатами правого нижнего угла области.  Флаг `--right_down`, значение задаётся в формате `right.down`, где right – координата по x, down – координата по y\n\tКопирование заданной области. Флаг для выполнения данной операции: `--copy`. Функционал определяется:\nКоординатами левого верхнего угла области-источника. Флаг `--left_up`, значение задаётся в формате `left.up`, где left – координата по x, up – координата по y\nКоординатами правого нижнего угла области-источника. Флаг `--right_down`, значение задаётся в формате `right.down`, где right – координата по x, down – координата по y\nКоординатами левого верхнего угла области-назначения. Флаг `--dest_left_up`, значение задаётся в формате `left.up`, где left – координата по x, up – координата по y\n\tЗаменяет все пиксели одного заданного цвета на другой цвет. Флаг для выполнения данной операции: `--color_replace`. Функционал определяется:\nЦвет, который требуется заменить. Флаг `--old_color` (цвет задаётся строкой `rrr.ggg.bbb`, где rrr/ggg/bbb – числа, задающие цветовую компоненту. пример `--old_color 255.0.0` задаёт красный цвет)\nЦвет на который требуется заменить. Флаг `--new_color` (работает аналогично флагу `--old_color`)\n\tРазделяет изображение на N*M частей линиями одинаковой толщины. Флаг для выполнения данной операции: `--split`. . Функционал определяется:\nКоличество частей по “оси” Y. Флаг `--number_x`. На вход принимает число больше 1\nКоличество частей по “оси” X. Флаг `--number_y`. На вход принимает число больше 1\nТолщина линии. Флаг `--thickness`. На вход принимает число больше 0\nЦвет линии. Флаг `--color` (цвет задаётся строкой `rrr.ggg.bbb`, где rrr/ggg/bbb – числа, задающие цветовую компоненту. пример `--color 255.0.0` задаёт красный цвет)\n"
#define MAX_COLOR 255