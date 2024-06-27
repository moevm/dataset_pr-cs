#include "image_editor.h"

void ImageEditor::rotate(int x_left, int y_left, int x_right, int y_right, int angle) {
  int x_max = std::min(x_right, image_.get_width() - 1),
	  y_max = std::min(y_left, image_.get_height() - 1);
  switch (angle) {
	case 90: rotate_90(x_left, y_max, x_max, y_right);
	  break;
	case 180: rotate_180(x_left, y_max, x_max, y_right);
	  break;
	case 270: rotate_270(x_left, y_max, x_max, y_right);
	  break;
	default: throw ImageEditorError(image_editor_errors::k_error_wrong_angle);
  }
}

void ImageEditor::rotate_90(int x_left, int y_left, int x_right, int y_right) {
  int x_center = (x_left + x_right) / 2, y_center = (y_left + y_right) / 2;
  std::vector<std::vector<Color>> colors_copy = image_.get_colors();

  for (int y = 0; y < y_left - y_right; y++) {
	for (int x = 0; x < x_right - x_left; x++) {
	  int x_new = x_center + (y_left - y_center) - y - 1, y_new = y_center + (x_right - x_center) - x - 1;
	  if (x_new >= image_.get_width() || x_new < 0 || y_new >= image_.get_height() || y_new < 0)
		continue;
	  colors_copy[y_new][x_new] = image_.get_color(x_left + x, y_left - y - 1);
	}
  }

  image_.set_colors(colors_copy);
}

void ImageEditor::rotate_180(int x_left, int y_left, int x_right, int y_right) {
  std::vector<std::vector<Color>> colors_copy = image_.get_colors();
  for (int y = 0; y < y_left - y_right; y++) {
	for (int x = 0; x < x_right - x_left; x++) {
	  colors_copy[y_right + y][x_right - x - 1] = image_.get_color(x_left + x, y_left - y - 1);
	}
  }
  image_.set_colors(colors_copy);
}

void ImageEditor::rotate_270(int x_left, int y_left, int x_right, int y_right) {
  int x_center = (x_left + x_right) / 2,
	  y_center = (y_left + y_right) / 2;
  std::vector<std::vector<Color>> colors_copy = image_.get_colors();

  for (int y = 0; y < y_left - y_right; y++) {
	for (int x = 0; x < x_right - x_left; x++) {
	  int x_new = x_center + (y_left - y_center) - y - 1, y_new = y_center + (x_right - x_center) - x - 1;
	  if (x_new >= image_.get_width() || x_new < 0 || y_new >= image_.get_height() || y_new < 0)
		continue;
	  colors_copy[y_new][x_new] = image_.get_color(x_right - x - 1, y_right + y);
	}
  }

  image_.set_colors(colors_copy);
}
