// try #2

#include <exception>
#include <iostream>
#include <stdexcept>

#include "options.hpp"
#include "image.hpp"

#define EXIT_OK 0
#define EXIT_BAD 40



int main(int argc, char **argv)
{
	puts("Course work for option 5.14, created by Kirill Gorsky");
	opterr = 0;

	Image image;
	Options opts;

	try {
		opts.readFromArgv(argc, argv);

		if (opts.func->do_read) {
			image.load(opts.input.c_str());
		}

		if ((opts.bits & opts.func->required_bits) != opts.func->required_bits)
			throw std::runtime_error("not enough arguments");

		int color_type = image.getColorType();
		if (opts.func->do_write && color_type != PNG_COLOR_TYPE_RGB && color_type != PNG_COLOR_TYPE_RGBA)
			throw std::runtime_error("bad color type");

		opts.func->ptr(image, opts);
		
		if (opts.func->do_write) {
			image.save(opts.output.c_str());
		}
	} catch (std::exception &e) {
		std::cerr << "error: " << e.what() << "\n";
		return EXIT_BAD;
	}

	return EXIT_OK;
}
