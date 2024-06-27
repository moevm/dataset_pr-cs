#include "image_editor.h"

void ImageEditor::circle_pixel(int size, Color color, Color circle_color) {
  for (int y = 0; y < image_.get_height(); y++) {
    for (int x = 0; x < image_.get_width(); x++) {
      if (image_.get_color(x, y) == color)
        circleit(x, y, size, color, circle_color);
    }
  }
}

void ImageEditor::circleit(int x_circle, int y_circle, int size, Color color, Color circle_color) {
  for (int y = y_circle - size; y <= y_circle + size; y++) {
    for (int x = x_circle - size; x <= x_circle + size; x++) {
      if (x < 0 || y < 0 || x >= image_.get_width() || y >= image_.get_height()) continue;
      if (image_.get_color(x, y) == color) continue;
      image_.set_color(x, y, circle_color);
    }
  }
}
