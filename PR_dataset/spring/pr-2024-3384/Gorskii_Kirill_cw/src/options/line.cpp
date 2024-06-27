#include "../options.hpp"

void processLineOption(Image &image, Options &opts)
{
	image.drawLine(opts.start, opts.end, opts.color, opts.thickness);
}
