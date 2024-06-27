#include "image_editor.h"

void ImageEditor::draw_rectangle(int x_left,
                                 int y_left,
                                 int x_right,
                                 int y_right,
                                 int thickness,
                                 Color line_color,
                                 bool fill,
                                 Color fill_color) {

  if (fill)
    fill_rectangle(x_left, y_left, x_right, y_right, fill_color);

  if (y_right - thickness < image_.get_height())
	for (int x = x_left; x <= x_right; x++)
      fill_circle(x, y_right, thickness, line_color);

  if (y_left - thickness < image_.get_height())
	for (int x = x_left; x <= x_right; x++)
      fill_circle(x, y_left, thickness, line_color);

  if (x_left - thickness < image_.get_width())
	for (int y = y_right; y <= y_left; y++)
      fill_circle(x_left, y, thickness, line_color);

  if (x_right - thickness < image_.get_width())
	for (int y = y_right; y <= y_left; y++)
      fill_circle(x_right, y, thickness, line_color);
}

void ImageEditor::fill_rectangle(int x_left,
                                 int y_left,
                                 int x_right,
                                 int y_right,
                                 Color color) {
  int x_max = std::min(x_right, image_.get_width() - 1),
	  y_max = std::min(y_left, image_.get_height() - 1);

  for (int y = y_right; y < y_max; y++) {
	for (int x = x_left; x < x_max; x++) {
      image_.set_color(x, y, color);
	}
  }
}