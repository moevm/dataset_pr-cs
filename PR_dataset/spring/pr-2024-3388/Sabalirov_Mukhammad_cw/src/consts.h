#pragma once

#define INPUT_ARG "input"
#define SHORT_INPUT_ARG 'i'
#define OUTPUT_ARG "output"
#define SHORT_OUTPUT_ARG 'o'
#define HELP_ARG "help"
#define SHORT_HELP_ARG 'h'
#define INFO_ARG "info"
#define MIRROR_ARG "mirror"
#define AXIS_ARG "axis"
#define PENTAGRAM_ARG "pentagram"
#define RECT_ARG "rect"
#define HEXAGON_ARG "hexagon"
#define CENTER_ARG "center"
#define RADIUS_ARG "radius"
#define FILL_COLOR_ARG "fill_color"
#define FILL_ARG "fill"
#define THICKNESS_ARG "thickness"
#define COLOR_ARG "color"
#define LEFT_UP_ARG "left_up"
#define RIGHT_DOWN_ARG "right_down"
#define PAVING_ARG "paving"

#define AXIS_CODE 1
#define CENTER_CODE 2
#define RADIUS_CODE 3
#define FILL_COLOR_CODE 4
#define FILL_CODE 5
#define THICKNESS_CODE 6
#define COLOR_CODE 7
#define LEFT_UP_CODE 8
#define RIGHT_DOWN_CODE 9

#define SHORT_OPTIONS "i:o:h"

#define UNKNOWN_OPTION_OR_NO_REQUIRED_ARG '?'
#define UNKNOWN_OPTION_OR_NO_REQUIRED_ARG_ERROR "Error: unknown option or no required argument"
#define UNKNOWN_OPTION '?'
#define UNKNOWN_OPTION_ERROR "Error: unknown option"
#define NO_REQUIRED_ARG ':'
#define NO_REQUIRED_ARG_ERROR "Error: no required argument"
#define FILENAME_ERROR "Error: input/output filename is not correct"
#define MAIN_FUNCTION_COUNT_ERROR "Error: main functions count not equal 1"
#define ARG_FORMAT_ERROR "Error: argument has not correct format or no requited argument"
#define LEFT_RIGHT_COORD_ERROR "Error: left_up_x > right_down_x or left_up_y > right_down_y"
#define PANIC_TEMPLATE "%s. Exit with code %d\n"

#define AXIS_FIRST_VAL "x"
#define AXIS_SECOND_VAL "y"
#define DEFAULT_OUTPUT "out.png"
#define FILENAME_EXTENSION ".png"
#define EXIT_CODE 40

#define REGCOMP_ERROR "Error: The regular expression could not be completed"
#define REGFIND_ERROR "Error: Regular expression match failed"
#define REGEX_COLOR_CHECK "^([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\\.([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\\.([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$"
#define REGEX_FILENAME_CHECK "^.*\\.png$"
#define REGEX_COORDS_CHECK "^[-]?[0-9]+\\.[-]?[0-9]+$"
#define REGEX_NATURAL_CHECK "^[1-9][0-9]*$"
#define CAPTURE_GROUP_COUNT 10
#define REGEX_COORDS "^([-]?[0-9]+)\\.([-]?[0-9]+)$"
#define REGEX_COLOR "^([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\\.([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])\\.([01]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])$"
#define X_MATCH_POS 1
#define Y_MATCH_POS 2
#define X_AXIS_INT 0
#define Y_AXIS_INT 1
#define R_MATCH_POS 1
#define G_MATCH_POS 2
#define B_MATCH_POS 3
#define NO_ARG -1

#define READ_FILE_ERROR "Error: can not read file"
#define NOT_PNG_ERROR "Error: file is not png"
#define PNG_STRUCT_ERROR "Error: png structure is not correct"
#define PNG_INFO_STRUCT_ERROR "Error: png info-structure is not correct"
#define NOT_RGB "Error: png image not have rgb color type"
#define SETJMP_ERROR "Error: work with failed"
#define PROCESS_IMG_ERROR "Error: process image failed"
#define WRITE_IMG_ERROR "Error: image write failed"
#define WRITE_END_IMG_ERROR "Error: end write image failed"
#define PARAMS_INFO_TEMPLATE "mirror: %d\npentagram: %d\nrect: %d\nhexagon: %d\nfill: %d\ninfo: %d\naxis: %d\nleft_up: %d.%d\nright_down: %d.%d\ncenter: %d.%d\nradius: %d\nthickness: %d\ncolor: %d.%d.%d\nfill_color: %d.%d.%d\ninput: %s\noutput: %s\n"
#define HEADER_LEN 8
#define PNG_INFO_TEMPLATE "width: %d\nheight: %d\ncolor_type: %d\nbit_depth: %d\n"
#define PIXEL_PARAMS_COUNT 3

#define HELP "Course work for option 5.15, created by Mukhammad Sabalirov.\nОтражение заданной области. Флаг для выполнения данной операции: `--mirror`. Этот функционал определяется:\nвыбором оси относительно которой отражать (горизонтальная или вертикальная). Флаг `--axis`, возможные значения `x` и `y`\nКоординатами левого верхнего угла области. Флаг `--left_up`, значение задаётся в формате `left.up`, где left – координата по x, up – координата по y\nКоординатами правого нижнего угла области.  Флаг `--right_down`, значение задаётся в формате `right.down`, где right – координата по x, down – координата по y\nРисование пентаграммы в круге. Флаг для выполнения данной операции: `--pentagram`. Пентаграмма определяется:\nкоординатами ее центра и радиусом. Флаги `--center` и `--radius`. Значение флаг `--center` задаётся в формате `x.y`, где x – координата по оси x, y – координата по оси y. Флаг `--radius` На вход принимает число больше 0\nтолщиной линий и окружности. Флаг `--thickness`. На вход принимает число больше 0\nцветом линий и окружности. Флаг `--color` (цвет задаётся строкой `rrr.ggg.bbb`, где rrr/ggg/bbb – числа, задающие цветовую компоненту. пример `--color 255.0.0` задаёт красный цвет)\nРисование прямоугольника. Флаг для выполнения данной операции: `--rect`. Он определяется:\nКоординатами левого верхнего угла. Флаг `--left_up`, значение задаётся в формате `left.up`, где left – координата по x, up – координата по y\nКоординатами правого нижнего угла.  Флаг `--right_down`, значение задаётся в формате `right.down`, где right – координата по x, down – координата по y\nТолщиной линий. Флаг `--thickness`. На вход принимает число больше 0\nЦветом линий. Флаг `--color` (цвет задаётся строкой `rrr.ggg.bbb`, где rrr/ggg/bbb – числа, задающие цветовую компоненту. пример `--color 255.0.0` задаёт красный цвет)\nПрямоугольник может быть залит или нет. Флаг `--fill`. Работает как бинарное значение: флага нет – false , флаг есть – true.\nцветом которым он залит, если пользователем выбран залитый. Флаг `--fill_color` (работает аналогично флагу `--color`)\nРисование правильного шестиугольника. Флаг для выполнения данной операции: `--hexagon`. Шестиугольник определяется:\nкоординатами его центра и радиусом в который он вписан. Флаги `--center` и `--radius`. Значение флаг `--center` задаётся в формате `x.y`, где x – координата по оси x, y – координата по оси y. Флаг `--radius` На вход принимает число больше 0\nтолщиной линий. Флаг `--thickness`. На вход принимает число больше 0\nцветом линий. Флаг `--color` (цвет задаётся строкой `rrr.ggg.bbb`, где rrr/ggg/bbb – числа, задающие цветовую компоненту. пример `--color 255.0.0` задаёт красный цвет)\nшестиугольник может быть залит или нет. Флаг `--fill`. Работает как бинарное значение: флага нет – false , флаг есть – true.\nцветом которым залит шестиугольник, если пользователем выбран залитый. Флаг `--fill_color` (работает аналогично флагу `--color`)\n"
#define END_OF_STR '\0'
#define THICK_K 2
#define PI 3.14159265358979323846