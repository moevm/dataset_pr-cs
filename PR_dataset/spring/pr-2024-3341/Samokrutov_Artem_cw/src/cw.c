#include "cwstructures/cwstructures.h"
#include "cwbmp/cwbmp.h"
#include "cwdrawing/cwdrawing.h"
#include "cwoptions/cwoptions.h"


void help()
{
	printf("This is a bitmap image processing program\n");
	printf("It accepts the followng command line arguments:\n");
	printf("\t--line: draws a line between two points of set color and thickness.\n");
	printf("\t\t--start x.y : sets the start at point (x, y);\n");
	printf("\t\t--end x.y : sets the end at (x, y);\n");
	printf("\t\t--color rrr.ggg.bbb : sets the color to an RGB with corresponding components;\n");
	printf("\t\t--thickness t : sets the thickness to t, has to be a positive number;\n");
	printf("\n");
	printf("\t--inverse_circle: inverts the pixels within a given circle.\n");
	printf("\t\t--center x.y : sets the center at point (x, y);\n");
	printf("\t\t--radius r : sets the radius to r, has to be a positive number;\n");
	printf("\n");
	printf("\t--trim: crops the image to a rectangle given by two points;\n");
	printf("\t\t--left_up x.y : sets the upper left point at (x, y);\n");
	printf("\t\t--right_down x.y : sets the down right point at (x, y);\n");
}

int main(int argc, char **argv) {
    printf("Course work for option 4.6, created by Artem Samokrutov\n");
    struct Config *config = get_options(argc, argv);

	if (config->flag_help == 1)
	{
		help();
		return 0;
	}

	if (config->flag_info == 1)
	{
		if (big_flag_is_set(config) ||
			strlen(config->output_file) != 0)
		{
			throw_error(CONFIG_ERROR_MSG, CONFIG_ERROR_RET_VAL);
		}

		info(config->input_file);
		return 0;
	}

	if (strlen(config->input_file) == 0)
	{
		throw_error(CONFIG_ERROR_MSG, CONFIG_ERROR_RET_VAL);
	}

	if (strcmp(config->input_file, config->output_file) == 0 || 
	    strcmp(config->input_file, "./out.bmp") == 0)
	{
		throw_error(CONFIG_ERROR_MSG, CONFIG_ERROR_RET_VAL);
	}
	
	Bitmap_image_t *image = load_bmp(config->input_file);

	if (config->flag_line)
	{
		draw_line(image,
				  config->line->start,
				  config->line->end,
				  config->line->color,
				  config->line->thickness);
	}

	if (config->flag_inverse_circle)
	{
		invert_circle(image,
		              config->inverse_circle->center,
					  config->inverse_circle->radius);
	}

	if (config->flag_trim)
	{
		crop(image,
		     config->trim->left_up,
			 config->trim->right_down);
	}

	if (config->flag_contrast)
	{
		contrast(image,
		         config->contrast->alpha,
				 config->contrast->beta);
	}

	if (strlen(config->output_file) == 0)
	{
		strcpy(config->output_file, "./out.bmp");
	}

	save_bmp(image, config->output_file);
	free_bmp(image);

    destroy_config(config);

    return 0;
}
