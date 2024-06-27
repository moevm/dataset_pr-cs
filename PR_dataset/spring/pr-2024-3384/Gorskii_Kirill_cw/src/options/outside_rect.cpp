#include "../options.hpp"
#include <stdexcept>

void processOutsideRectOption(Image &image, Options &opts)
{
	int dx = opts.right_down.x - opts.left_up.x;
	int dy = opts.right_down.y - opts.left_up.y;

	if (dx < 0 || dy < 0) {
		throw std::logic_error("invalid region");
	}

	for (int y = 0; y < (int)image.getHeight(); y++) {
		for (int x = 0; x < (int)image.getWidth(); x++) {
			if (x > opts.right_down.x || x < opts.left_up.x || y > opts.right_down.y || y < opts.left_up.y) {
				image.setPixel(vec2i(x, y), opts.color);
			}
		}
	}
}
