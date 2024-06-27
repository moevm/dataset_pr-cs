#pragma once
#define GAMMA_ARG "gamma"
#define VALUE_ARG "value"
#define HELP "Course work for option 4.23, created by Viktoriya Glebova.\n(1) Рисование окружности. Флаг для выполнения данной операции: `--circle`. Окружность определяется:\nкоординатами ее центра и радиусом. Флаги `--center` и `--radius`. Значение флаг `--center` задаётся в формате `x.y`, где x – координата по оси x, y – координата по оси y. Флаг `--radius` На вход принимает число больше 0\nтолщиной линии окружности. Флаг `--thickness`. На вход принимает число больше 0\nцветом линии окружности. Флаг `--color` (цвет задаётся строкой `rrr.ggg.bbb`, где rrr/ggg/bbb – числа, задающие цветовую компоненту. пример `--color 255.0.0` задаёт красный цвет)\nокружность может быть залитой или нет. Флаг `--fill`. Работает как бинарное значение: флага нет – false , флаг есть – true.\nцветом которым залита сама окружность, если пользователем выбрана залитая окружность. Флаг `--fill_color` (работает аналогично флагу `--color`)\n(2) Фильтр rgb-компонент. Флаг для выполнения данной операции: `--rgbfilter`. Этот инструмент должен позволять для всего изображения либо установить в диапазоне от 0 до 255 значение заданной компоненты. Функционал определяется\nКакую компоненту требуется изменить. Флаг `--component_name`. Возможные значения `red`, `green` и `blue`.\nВ какой значение ее требуется изменить. Флаг `--component_value`. Принимает значение в виде числа от 0 до 255\n(3) Разделяет изображение на N*M частей. Флаг для выполнения данной операции: `--split`. Реализация: провести линии заданной толщины. Функционал определяется:\nКоличество частей по “оси” Y. Флаг `--number_x`. На вход принимает число больше 1\nКоличество частей по “оси” X. Флаг `--number_y`. На вход принимает число больше 1\nТолщина линии. Флаг `--thickness`. На вход принимает число больше 0\nЦвет линии. Флаг `--color` (цвет задаётся строкой `rrr.ggg.bbb`, где rrr/ggg/bbb – числа, задающие цветовую компоненту. пример `--color 255.0.0` задаёт красный цвет)\n"
#define OK_CODE 0
#define NONE_VALUE -1

#define EXIT_CODE 44
#define ERROR_TEMPLATE "%s. Exit code: %d\n"

#define ALLOC_ERROR "Error: allocate of memory"

#define NO_ARG_VAL_ERROR "Error: argument required value"
#define UNKNOWN_ARG_ERROR "Error: unknown argument"
#define NO_INPUT_FILE_ARG_ERROR "Error: not geted input-file"

#define REGCOMP_ERROR "Error: The regular expression could not be completed"

#define SELECTED_FUNCTIONS_COUNT_ERROR "Error: selected funtions count not equal 1"
#define SELECTED_FUNCTIONS_COUNT_ERROR_CODE 2
#define ARG_VAL_ERROR "Error: argument(s) value is not correct"
#define ARG_VAL_ERROR_CODE 3
#define READ_FILE_ERROR "Error: can not read file"
#define NOT_PNG_ERROR "Error: file is not png"
#define PNG_STRUCT_ERROR "Error: png structure is not correct"
#define PNG_INFO_STRUCT_ERROR "Error: png info-structure is not correct"
#define NOT_RGB "Error: png image not have rgb color type"
#define SETJMP_ERROR "Error: work with failed"
#define PROCESS_IMG_ERROR "Error: process image failed"
#define WRITE_IMG_ERROR "Error: image write failed"
#define WRITE_END_IMG_ERROR "Error: end write image failed"
#define HEADER_LEN 8
#define IMG_INFO "width: %d\nheight: %d\ncolor_type: %d\nbit_depth: %d\n"
#define PIXEL_PARAMS_COUNT 3

#define DEFAULT_OUTPUT_PNG "out.png"

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
#define CENTER_ARG "center"
#define RADIUS_ARG "radius"
#define THICKNESS_ARG "thickness"
#define CIRCLE_ARG "circle"
#define RGB_FILTER "rgbfilter"
#define SPLIT_ARG "split"
#define FILL_ARG "fill"
#define FILL_COLOR_ARG "fill_color"
#define COMPONENT_NAME_ARG "component_name"
#define COMPONENT_VALUE_ARG "component_value"
#define NUMBER_X_ARG "number_x"
#define NUMBER_Y_ARG "number_y"

#define RADIUS_KOEFF 2
#define PENTAGRAM_ANGEL_COUNT 5
#define PI 3.14159265358979323846

#define END_STR '\0'
#define REGEX_NATURAL_NUM "^[1-9][0-9]*$"
#define REGEX_NUM "^[0-9]*$"
#define REGEX_COORDINATES "^([-]?[0-9]+)\\.([-]?[0-9]+)$"
#define REGEX_RGB_FILTER "^(red|green|blue)$"
#define REGEX_COLOR "^([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\\.([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\\.([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$"
#define MAX_CAPTURE_GROUP 4

#define RED_VAL "red"
#define GREEN_VAL "green"
#define BLUE_VAL "blue"

#define MAX_COMPONENT_VAL 255