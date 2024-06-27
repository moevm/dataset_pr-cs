#include "image_editor_ornaments.h"

void ImageEditor::draw_ornament(int pattern, Color line_color, int thickness, int count) {
  switch (pattern) {
	case ornaments::k_rectangle: draw_rectangle_ornament(thickness, line_color, count);
	  break;
	case ornaments::k_circle: draw_circle_ornament(line_color);
	  break;
	case ornaments::k_semicircle: draw_semi_circles_ornament(thickness, line_color, count);
	  break;
  }
}

void ImageEditor::draw_rectangle_ornament(int thickness, Color line_color, int count) {
  for (int c = 0; c < count; c++) {
	for (int t = 0; t < thickness; t++) {
	  int offset = t + c * thickness * 2;
	  for (int y = 0 + offset; y < image_.get_height() - offset; y++) {
        image_.set_color(0 + offset, y, line_color);
        image_.set_color(image_.get_width() - 1 - offset, y, line_color);
	  }
	  for (int x = 0 + offset; x < image_.get_width() - offset; x++) {
        image_.set_color(x, 0 + offset, line_color);
        image_.set_color(x, image_.get_height() - 1 - offset, line_color);
	  }
	}
  }
}

void ImageEditor::draw_circle_ornament(Color line_color) {
  int radius = std::min(image_.get_width(), image_.get_height()) / 2;
  int x_center = image_.get_width() / 2, y_center = image_.get_height() / 2;
  std::vector<std::vector<Color>> colors(image_.get_height(),
										 std::vector<Color>(image_.get_width(), line_color));

  for (int y = 0; y < radius; y++) {
	for (int x = 0; x < radius; x++) {
	  if ((x * x + y * y) >= radius * radius) continue;
	  colors[y_center + y][x_center + x] = image_.get_color(x_center + x, y_center + y); // 1 sector
	  colors[y_center + y][x_center - x] = image_.get_color(x_center - x, y_center + y); // 2 sector
	  colors[y_center - y][x_center - x] = image_.get_color(x_center - x, y_center - y); // 3 sector
	  colors[y_center - y][x_center + x] = image_.get_color(x_center + x, y_center - y); // 4 sector
	}
  }
  image_.set_colors(colors);
}

void ImageEditor::draw_semi_circles_ornament(int thickness, Color line_color, int count) {
  // X-axis
  int x_radius = std::ceil((float) image_.get_width() / (2 * (float)count));
  int x = x_radius;
  while (x < image_.get_width()) {
    draw_circle(x, image_.get_height() - 1, x_radius, thickness, line_color);
    draw_circle(x, 0, x_radius, thickness, line_color);
	x += x_radius * 2;
  }
  // Last circle after border
  if (image_.get_width() % count != 0) {
    draw_circle(x, image_.get_height() - 1, x_radius, thickness, line_color);
    draw_circle(x, 0, x_radius, thickness, line_color);
  }

  // Y-axis
  int y_radius = std::ceil((float) image_.get_height() / (2 * (float)count));
  int y = y_radius;
  while (y < image_.get_height()) {
    draw_circle(0, y, y_radius, thickness, line_color);
    draw_circle(image_.get_width() - 1, y, y_radius, thickness, line_color);
	y += y_radius * 2;
  }
  // Last circle after border
  if (image_.get_height() % count != 0) {
    draw_circle(0, y, y_radius, thickness, line_color);
    draw_circle(image_.get_width() - 1, y, y_radius, thickness, line_color);
  }
}