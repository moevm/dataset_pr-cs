#pragma once

#include <getopt.h>
#include <cstdio>
#include <string>
#include <cstring>

#include "regex_validation.h" // parsing values
#include "../image_editor_lib/image_editor_ornaments.h"
#include "args_errors.h"

namespace args_config {

// Exceptions
const char *const k_default_file_output = "./out.bmp";

// Short-arguments
const char *const k_short_options = "i:o:h";
const char k_short_input = 'i';
const char k_short_output = 'o';
const char k_short_help = 'h';
const char k_short_unknown = '?';
const char k_short_missing = ':';

// Functions (long arguments)
const char *const k_rectangle = "rect";
const char *const k_ornament = "ornament";
const char *const k_rotate = "rotate";
const char *const k_circle = "circle";

const char *const k_input = "input";
const char *const k_output = "output";
const char *const k_help = "help";

// Values for functions (long arguments)
const char *const k_left_up = "left_up";
const char *const k_right_down = "right_down";
const char *const k_center = "center";
const char *const k_thickness = "thickness";
const char *const k_radius = "radius";
const char *const k_angle = "angle";
const char *const k_pattern = "pattern";
const char *const k_count = "count";
const char *const k_color = "color";
const char *const k_fill = "fill";
const char *const k_fill_color = "fill_color";
const char *const k_info = "info";

const char *const k_concat = "concat";
const char *const k_axis = "axis";
const char *const k_input_second = "input_second";

const char *const k_circle_pixel = "circle_pixel";
const char *const k_size = "size";
const char *const k_circle_color = "circle_color";



const char *const k_help_text = "Course work for option 5.1, created by Aleksandr Izhboldin.\n"
							  "Рисование прямоугольника. Флаг для выполнения данной операции: `--rect`. Он определяется:\n"
							  "Координатами левого верхнего угла. Флаг `--left_up`, значение задаётся в формате `left.up`, где left – координата по x, up – координата по y\n"
							  "Координатами правого нижнего угла.  Флаг `--right_down`, значение задаётся в формате `right.down`, где right – координата по x, down – координата по y\n"
							  "Толщиной линий. Флаг `--thickness`. На вход принимает число больше 0\n"
							  "Цветом линий. Флаг `--color` (цвет задаётся строкой `rrr.ggg.bbb`, где rrr/ggg/bbb – числа, задающие цветовую компоненту. пример `--color 255.0.0` задаёт красный цвет)\n"
							  "Прямоугольник может быть залит или нет. Флаг `--fill`. Работает как бинарное значение: флага нет – false , флаг есть – true.\n"
							  "цветом которым он залит, если пользователем выбран залитый. Флаг `--fill_color` (работает аналогично флагу `--color`)\n"
							  "Сделать рамку в виде узора. Флаг для выполнения данной операции: `--ornament`. Рамка определяется:\n"
							  "Узором. Флаг `--pattern`. Обязательные значения: rectangle и circle, semicircles.\n"
							  "Цветом. Флаг `--color` (цвет задаётся строкой `rrr.ggg.bbb`, где rrr/ggg/bbb – числа, задающие цветовую компоненту. пример `--color 255.0.0` задаёт красный цвет)\n"
							  "Шириной. Флаг `--thickness`. На вход принимает число больше 0\n"
							  "Количеством. Флаг `--count`. На вход принимает число больше 0\n"
							  "При необходимости можно добавить дополнительные флаги для необозначенных узоров\n"
							  "Поворот изображения (части) на 90/180/270 градусов. Флаг для выполнения данной операции: `--rotate`. Функционал определяется\n"
							  "Координатами левого верхнего угла области. Флаг `--left_up`, значение задаётся в формате `left.up`, где left – координата по x, up – координата по y\n"
							  "Координатами правого нижнего угла области.  Флаг `--right_down`, значение задаётся в формате `right.down`, где right – координата по x, down – координата по y\n"
							  "Углом поворота. Флаг `--angle`, возможные значения: `90`, `180`, `270`\n"
							  "Рисование окружности. Флаг для выполнения данной операции: `--circle`. Окружность определяется:\n"
							  "координатами ее центра и радиусом. Флаги `--center` и `--radius`. Значение флаг `--center` задаётся в формате `x.y`, где x – координата по оси x, y – координата по оси y. Флаг `--radius` На вход принимает число больше 0\n"
							  "толщиной линии окружности. Флаг `--thickness`. На вход принимает число больше 0\n"
							  "цветом линии окружности. Флаг `--color` (цвет задаётся строкой `rrr.ggg.bbb`, где rrr/ggg/bbb – числа, задающие цветовую компоненту. пример `--color 255.0.0` задаёт красный цвет)\n"
							  "окружность может быть залитой или нет. Флаг `--fill`. Работает как бинарное значение: флага нет – false , флаг есть – true.\n"
							  "цветом которым залита сама окружность, если пользователем выбрана залитая окружность. Флаг `--fill_color` (работает аналогично флагу `--color`)\n";

}

enum class ArgCodes {
  k_left_up = 1,
  k_right_down,
  k_center,
  k_thickness,
  k_radius,
  k_angle,
  k_pattern,
  k_count,
  k_color,
  k_fill_color,
  k_info,
  k_axis,
  k_input_second,
  k_size,
  k_circle_color,
  k_circle_pixel
};

class Args {
 public:
  int help = false;
  int info = false;
  int rectangle = false;
  int ornament = false;
  int rotate = false;
  int circle = false;
  std::pair<int, int> left_up;
  std::pair<int, int> right_down;
  std::pair<int, int> center;
  int radius = 0;
  int thickness = 0;
  int count = 0;
  int angle = 0;
  int pattern = 0;
  Color color;
  int fill = false;
  Color fill_color;

  int concat = false;
  int axis = -1;
  std::string input_second_file;

  int circle_pixel = false;
  int size = 0;
  Color circle_color;

  std::string input_file;
  std::string output_file = args_config::k_default_file_output;

  Args(int argc, char **argv);
  ~Args() = default;

  void print_info() const;

 private:

  bool is_color_set_ = false;
  bool is_fill_color_set_ = false;
  bool is_circle_color_set_ = false;
  bool is_left_up_set_ = false;
  bool is_right_down_set_ = false;
  bool is_center_set_ = false;

  void parse_long_argument(int &arg_code);
  bool check_arguments();
  static bool is_ok_pattern(const std::string &str);
  bool is_coordinates_set() const;
  bool is_fill_set() const;
  void parse_left_up_arg();
  void parse_right_down_arg();
  void parse_center_arg();
  void parse_thickness_arg();
  void parse_radius_arg();
  void parse_angle_arg();
  void parse_pattern_arg();
  void parse_count_arg();
  void parse_color_arg();
  void parse_fill_color_arg();
  void parse_axis_arg();
  void parse_circle_color_arg();
  void parse_size_arg();
};


