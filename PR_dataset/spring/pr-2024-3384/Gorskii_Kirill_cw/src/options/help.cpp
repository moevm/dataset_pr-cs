#include "../options.hpp"

void processHelpOption(Image &image, Options &opts)
{
    static char help_message[] = 
		"Usage: cw option parameters... out_file\n"
		"List of options:\n"
		"  -h, --help                   Print help message\n"
		"  -T, --triangle               Draw a triangle\n"
		"  -R, --biggest_rect           Change color of the biggest rectangle\n"
		"  -C, --collage                Draw a collage\n"
		"  -L, --line                   Draw a line\n"
		"  -B, --blank                  Fill the image with white color\n"
        "  -i, --info                   Print information about the image\n"
		"\n"
		"List of parameters for triangle:\n"
		"  -p, --points x1.y1.x2.y2.x3.y3 Sets points of a triangle\n"
	    "  -c, --color rrr.ggg.bbb      Sets color of a triangle\n"
		"  -f, --fill                   Sets if the triangle is filled\n"
		"  --fill_color rrr.ggg.bbb     Sets fill color of a triangle\n"
		"                                 (if -f is set)\n"
		"  --bias x                     Sets bias of a triangle\n"
		"                                 (optional, default is 0.0)\n"
		"\n"
		"List of parameters for biggest_rect:\n"
		"  --old_color rrr.ggg.bbb      Sets color of rect to find\n"
		"  --new_color rrr.ggg.bbb      Sets new color of found rect\n"
		"\n"
		"List of parameters for collage:\n"
		"  -x, --number_x               Sets width of the collage\n"
		"  -y, --number_y               Sets height of the collage\n"
		"\n"
		"List of parameters for line:\n"
		"  -s, --start x.y              Sets start point of the line\n"
		"  -e, --end   x.y              Sets end point of the line\n"
		"  -c, --color rrr.ggg.bbb      Sets color of the line\n"
		"  -t, --thickness              Sets thickness of the line";

	puts(help_message);
}