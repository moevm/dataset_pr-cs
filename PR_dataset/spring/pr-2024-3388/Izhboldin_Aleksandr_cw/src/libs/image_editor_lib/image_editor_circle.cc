#include "image_editor.h"

void ImageEditor::draw_circle(int x_center,
                              int y_center,
                              int radius,
                              int thickness,
                              Color line_color,
                              bool fill,
                              Color fill_color) {
  int x = 0, y = radius, delta = 1 - 2 * radius, error = 0;

  if (fill)
    fill_circle(x_center, y_center, radius, fill_color);

  int fillRadius = (thickness + 1) / 2;

  while (y >= x) {
    fill_circle(x_center + y, y_center + x, fillRadius, line_color); // 1 sector
    fill_circle(x_center + x, y_center + y, fillRadius, line_color); // 2 sector
    fill_circle(x_center - x, y_center + y, fillRadius, line_color); // 3 sector
    fill_circle(x_center - y, y_center + x, fillRadius, line_color); // 4 sector
    fill_circle(x_center - y, y_center - x, fillRadius, line_color); // 5 sector
    fill_circle(x_center - x, y_center - y, fillRadius, line_color); // 6 sector
    fill_circle(x_center + x, y_center - y, fillRadius, line_color); // 7 sector
    fill_circle(x_center + y, y_center - x, fillRadius, line_color); // 8 sector

	error = 2 * (delta + y) - 1;
	if ((delta < 0) && (error <= 0)) {
	  delta += 2 * ++x + 1;
	  continue;
	}
	if ((delta > 0) && (error > 0)) {
	  delta -= 2 * --y + 1;
	  continue;
	}
	delta += 2 * (++x - --y);
  }
}

void ImageEditor::fill_circle(int x_center, int y_center, int radius, Color color) {
  if (x_center - radius >= image_.get_width() && y_center - radius >= image_.get_height()) return;
  if (x_center + radius < 0 && y_center + radius < 0) return;
  int x_min = std::max(0, x_center - radius);
  int y_min = std::max(0, y_center - radius);
  int x_max = std::min(image_.get_width() - 1, x_center + radius);
  int y_max = std::min(image_.get_height() - 1, y_center + radius);

  for (int y = y_min; y <= y_max; y++) {
	for (int x = x_min; x <= x_max; x++) {
	  int x_new = x - x_center, y_new = y - y_center;
	  if (x_new * x_new + y_new * y_new <= radius * radius) {
        image_.set_color(x, y, color);
	  }
	}
  }
}

