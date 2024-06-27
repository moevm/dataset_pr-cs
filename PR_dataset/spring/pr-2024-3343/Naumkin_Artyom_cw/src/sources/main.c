#include "bmp.h"
#include "errors.h"
#include "function_params.h"
#include "processing.h"
#include <stdlib.h>

int main(int argc, char* argv[])
{
    params_t* params = parse_command_line(argc, argv);
    bmp_file_t* bmp_file = read_bmp(params->input_file);

    if (params->info)
        print_info_header(bmp_file->dibh);
    else if (params->inverse_circle)
        inverse_inside_circle(bmp_file, params->p0, params->circle_r);
    else if (params->trim)
        crop_image(bmp_file, params->p0, params->p1);
    else if (params->triangle)
        draw_triangle(bmp_file, params->p0, params->p1, params->p2, params->color, params->thickness, params->fill, params->fill_color);
    else if (params->line)
        draw_line(bmp_file, params->p0, params->p1, params->thickness, params->color);
    else if (params->circle_pixel)
        circle_pixel(bmp_file, bmp_file->dibh.width, bmp_file->dibh.height, params->color, params->circle_color, params->size);

    write_bmp(params->output_file, bmp_file);
    free_bmp_file(bmp_file);
    free(params);
    return EXIT_SUCCESS;
}
