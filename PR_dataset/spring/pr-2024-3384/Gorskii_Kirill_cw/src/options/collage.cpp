#include "../options.hpp"
#include <stdexcept>

void processCollageOption(Image &image, Options &args)
{
	if (args.number_x <= 0 || args.number_y <= 0)
		throw std::logic_error("number_x and number_y must be greater than 0");

	uint32_t old_width = image.getWidth();
	uint32_t old_height = image.getHeight();
	image.resize(
		image.getWidth() * args.number_x,
		image.getHeight() * args.number_y
	);

	for (uint32_t y = 0; y < image.getHeight(); y++) {
		for (uint32_t x = 0; x < image.getWidth(); x++) {
			rgba32 color = image.getPixel(vec2i(x % old_width, y % old_height));
			image.setPixel(vec2i(x, y), color);
		}
	}
}