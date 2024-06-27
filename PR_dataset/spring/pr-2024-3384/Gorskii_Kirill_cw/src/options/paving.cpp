#include "../options.hpp"
#include <stdexcept>

void processPavingOption(Image &image, Options &opts)
{
	int dx = opts.right_down.x - opts.left_up.x;
	int dy = opts.right_down.y - opts.left_up.y;
	int x0 = opts.left_up.x;
	int y0 = opts.left_up.y;

	if (dx <= 0 || dy <= 0) {
		throw std::logic_error("invalid region");
	}
	
	uint8_t **new_rows = (uint8_t**)malloc(sizeof(uint8_t*) * dy);
	for (int i = 0; i < dy; i++) {
		new_rows[i] = (uint8_t*)malloc(sizeof(uint8_t) * dx * 3);
	}

	for (int y = 0; y < dy; y++) {
		for (int x = 0; x < dx; x++) {
			rgba32 col = image.getPixel(vec2i(x + x0, y + y0));
			new_rows[y][x * 3] = col.r;
			new_rows[y][x * 3 + 1] = col.g;
			new_rows[y][x * 3 + 2] = col.b;
		}
	}

	for (uint32_t y = 0; y < image.getHeight(); y++) {
		for (uint32_t x = 0; x < image.getWidth(); x++) {
			rgba32 col;
			col.r = new_rows[(y % dy)][(x % dx) * 3];
			col.g = new_rows[(y % dy)][(x % dx) * 3 + 1];
			col.b = new_rows[(y % dy)][(x % dx) * 3 + 2];
			col.a = 0xFF;
			image.setPixel(vec2i(x, y), col);
		}
	}
}
