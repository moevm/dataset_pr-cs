#include "../options.hpp"

void processBlankOption(Image &image, Options &args)
{
	image.fillRect(
		rect2i(vec2i(0, 0), vec2i(image.getWidth(), image.getHeight())),
		rgba32(0xFFFFFFFF)
	);
}