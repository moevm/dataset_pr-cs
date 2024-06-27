#include "image_editor.h"

void ImageEditor::draw_line(int x_left, int y_left, int x_right, int y_right, int thickness, Color line_color) {
  int dx = (x_right - x_left >= 0 ? 1 : -1);
  int dy = (y_right - y_left >= 0 ? 1 : -1);

  int x_len = abs(x_right - x_left);
  int y_len = abs(y_left - y_right);

  int len = std::max(x_len, y_len);
  if (len == 0)
    fill_circle(x_left, y_left, thickness, line_color);

  if (y_len <= x_len) {
	int x = x_left, y = y_left, d = -x_len;
	len++;
	while (len--) {
      fill_circle(x, y, thickness, line_color);
	  x += dx;
	  d += 2 * y_len;
	  if (d > 0) {
		d -= 2 * x_len;
		y += dy;
	  }
	}
  } else {
	int x = x_left, y = y_left, d = -y_len;
	len++;
	while (len--) {
      fill_circle(x, y, thickness, line_color);
	  y += dy;
	  d += 2 * x_len;
	  if (d > 0) {
		d -= 2 * y_len;
		x += dx;
	  }
	}
  }

}