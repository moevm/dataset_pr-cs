#include "../options.hpp"
#include <stdexcept>

void processTriangleOption(Image &image, Options &args)
{
	if (args.fill) {
		if ((args.bits & (1 << (OPTION_FILL_COLOR - OPTIONS_OFFSET))) == 0)
			throw std::logic_error("not enough arguments speified");

		image.fillTriangle(
			args.points[0], args.points[1], args.points[2],
			args.fill_color, args.bias
		);
	}

	image.drawTriangle(
		args.points[0], args.points[1], args.points[2],
		args.color, args.thickness
	);
}