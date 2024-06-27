#pragma once

#include <cmath>

#include "../bmp_image_lib/bmp_image_class.h"
#include "image_editor_errors.h"

class ImageEditor {
 public:
  explicit ImageEditor(BmpImage &image);
  ~ImageEditor() = default;

  // image_editor_rotate
  void rotate(int x_left, int y_left, int x_right, int y_right, int angle);

  // image_editor_line
  void draw_line(int x_left,
                 int y_left,
                 int x_right,
                 int y_right,
                 int thickness,
                 Color line_color);

  // image_editor_rectangle
  void draw_rectangle(int x_left,
                      int y_left,
                      int x_right,
                      int y_right,
                      int thickness,
                      Color line_color,
                      bool fill = false,
                      Color fill_color = Color());

  // image_editor_circle
  void draw_circle(int x_center,
                   int y_center,
                   int radius,
                   int thickness,
                   Color line_color,
                   bool fill = false,
                   Color fill_color = Color());

  // image_editor_ornament
  void draw_ornament(int pattern, Color line_color, int thickness = 0, int count = 0);

  void circle_pixel(int size, Color color, Color circle_color);

 private:
  BmpImage &image_;

  // image_editor_rotate
  void rotate_90(int x_left, int y_left, int x_right, int y_right);
  void rotate_180(int x_left, int y_left, int x_right, int y_right);
  void rotate_270(int x_left, int y_left, int x_right, int y_right);

  // image_editor_rectangle
  void fill_rectangle(int x_left, int y_left, int x_right, int y_right, Color color);

  // image_editor_circle
  void fill_circle(int x_center, int y_center, int radius, Color color);

  // image_editor_ornament
  void draw_rectangle_ornament(int thickness, Color line_color, int count);
  void draw_circle_ornament(Color line_color);
  void draw_semi_circles_ornament(int thickness, Color line_color, int count);

  void circleit(int x_circle, int y_circle, int size, Color color, Color circle_color);
};

