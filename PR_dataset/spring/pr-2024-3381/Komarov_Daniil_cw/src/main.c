#include "include/image.h"
#include "include/tasks.h"
#include "include/argparse.h"
#include "include/argdict.h"
#include "include/errors.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h> 

int main(int argc, char **argv)
{
    puts("Course work for option 5.14, created by Daniil Komarov");
    ArgDict *argdict; 
    enum Mode mode;
    // This function parses all the arguments data
    int status_code = argparse_parse(argc, argv, &argdict, &mode);

    if(status_code != RETCODE_OK) return handle_error(status_code);
    
    // If no mode choosed and no --info flag, or if -h presented
    if((argdict_find(argdict, ARG_PRINT_INFO, NULL) &&
       mode == MODE_NONE) || mode == MODE_HELP)
    {
        argparse_show_help();
        argdict_del(argdict);
        return RETCODE_OK;
    }

    // All other tasks require input_filename, parsing it
    char* input_filename;
    argdict_find(argdict, ARG_INPUT_NAME, &input_filename);
    
    if(argdict_find(argdict, ARG_PRINT_INFO, NULL) == 0)
    {
        // Required arg - input file - already checked
        // Argument data isn't used later, so freeing it
        status_code = task_print_file_info(input_filename);
        
        argdict_del(argdict);
        free(input_filename);

        return handle_error(status_code);
    }

    // All other tasks also require output_filename & compression_level
    char* output_filename;
    argdict_find(argdict, ARG_OUTPUT_NAME, &output_filename);
    char *compression_s;
    argdict_find(argdict, ARG_COMPRESSION, &compression_s);
    int64_t compression_level;
    status_code = argparse_int(compression_s, &compression_level);
    free(compression_s);
    if(status_code || compression_level < 0 || compression_level > 9)
    {
        fprintf(stderr, WRONG_ARG, "--compression", "<positive int>(0...9)");
        argdict_del(argdict);
        free(input_filename);
        free(output_filename);
        return RETCODE_ARG_ERROR;
    }

    // Test for input_filename == output_filename
    struct stat input_file_stat;
    struct stat output_file_stat;
    status_code = stat(input_filename, &input_file_stat) ||
                  stat(output_filename, &output_file_stat);

    if(status_code && input_file_stat.st_dev == output_file_stat.st_dev &&
       input_file_stat.st_ino == output_file_stat.st_ino)
    {
        fprintf(stderr, SAME_FILES_ERR);
        argdict_del(argdict);
        free(input_filename);
        free(output_filename);
        return RETCODE_IO_ERROR;
    }
    
    if(mode == MODE_TRIANGLE)
    {
        int64_t coords[6]; //x1, y1, x2, y2, x3, y3
        uint32_t thickness;
        uint8_t fill;
        Pixel color, fcolor;
        
        status_code = argparse_mode_triangle(argdict, coords,
                &thickness, &color, &fill, &fcolor);

        if(status_code == RETCODE_OK)
        {
            status_code = task_draw_triangle(input_filename, output_filename,
                coords, thickness, color, fill, fcolor, compression_level);
        }        
    }

    if(mode == MODE_COLLAGE)
    {
        uint32_t number_x, number_y;

        status_code = argparse_mode_collage(argdict, &number_x, &number_y);
        
        if(status_code == RETCODE_OK)
        {
            status_code = task_create_collage(input_filename, output_filename,
                number_x, number_y, compression_level);
        }
    }

    if(mode == MODE_RECT_SEARCH)
    {
        Pixel old_color, new_color;

        status_code = argparse_mode_rect(argdict, &old_color, &new_color);
        
        if(status_code == RETCODE_OK)
        {
            status_code = task_rect_search(input_filename, output_filename,
                old_color, new_color, compression_level);
        }
    }

    if(mode == MODE_LINE)
    {
        int64_t coords[4]; //x0, y0, x1, y1
        uint32_t thickness;
        Pixel color;
        
        status_code = argparse_mode_line(argdict, coords,
                &thickness, &color);

        if(status_code == RETCODE_OK)
        {
            status_code = task_draw_line(input_filename, output_filename,
                coords, thickness, color, compression_level);
        }
    }

    if(mode == MODE_ORNAMENT)
    {
        uint32_t thickness;
        Pixel color;

        status_code = argparse_mode_ornament(argdict, &thickness, &color);

        if(status_code == RETCODE_OK)
        {
            status_code = task_draw_outside_ornament(input_filename, output_filename,
                thickness, color, compression_level);
        }
    }
    
    argdict_del(argdict);
    free(input_filename);
    free(output_filename);
    return handle_error(status_code);
}
