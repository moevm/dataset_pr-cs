#include "../include/argparse.h"

#define safe_free(var) {if(var != NULL) {free(var);}}

// Parse arguments passed to main
// 
// Arguments:
// argc - argc from main()
// argv - argv from main()
//
// Return (as data at passed pointers):
// **argdict_ptr is ptr to ArgDict object, that stores all the parsed data
// *mode_ptr is ptr to selected mode (MODE_NONE, when no mode flags passed)
//
// Return (code):
// Return codes should be handled with handle_error() from "errors.h"
int argparse_parse(int argc, char **argv, ArgDict **argdict_ptr,
                   enum Mode *mode_ptr)
{
    enum Mode mode = MODE_NONE;
    ArgDict *dict = argdict_new(); 
    if(dict == NULL) return RETCODE_MEMORY_ERROR;
    
    // Set default filename and no output compression
    int status_code = argdict_set(dict, ARG_OUTPUT_NAME, "out.png") ||
                      argdict_set(dict, ARG_COMPRESSION, "0");
    if(status_code)
    {
        argdict_del(dict);
        return status_code;
    }
    int argparse_err = 0;

    // Long options
    const struct option long_options[] = {
        {"help",         no_argument,       NULL, 'h'},
        {"input",        required_argument, NULL, 'i'},
        {"output",       required_argument, NULL, 'o'},
        {"info",         no_argument,       NULL, 'I'},
        {"triangle",     no_argument,       NULL, 't'},
        {"points",       required_argument, NULL, 'P'},
        {"thickness",    required_argument, NULL, 'T'},
        {"color",        required_argument, NULL, 'C'},
        {"fill",         no_argument,       NULL, 'f'},
        {"fill_color",   required_argument, NULL, 'F'},
        {"biggest_rect", no_argument,       NULL, 'b'},
        {"old_color",    required_argument, NULL, 'O'},
        {"new_color",    required_argument, NULL, 'N'},
        {"collage",      no_argument,       NULL, 'c'},
        {"number_x",     required_argument, NULL, 'X'},
        {"number_y",     required_argument, NULL, 'Y'},
        {"line",         no_argument,       NULL, 'l'},
        {"start",        required_argument, NULL, 'S'},
        {"end",          required_argument, NULL, 'E'},
        {"compression",  required_argument, NULL, 'z'},
        {"outside_ornament", no_argument,   NULL, 'r'},
        {0, 0, 0, 0}
    };
    
    while(!argparse_err) {
        // Short arguments in the next line are completely
        // identical to 4th "value" field of long options above
        // so there's only one switch operator that handles
        // both short and long options
        int c = getopt_long(argc, argv,
            "hi:o:ItP:T:C:fF:bO:N:cY:X:lS:E:z:r", long_options, NULL);

        // If already parsed all arguments
        if(c == -1) break;
        
        // Help flag placed here, because if it is presented
        // program should show help and ignore other arguments
        if(c == 'h')
        {
            mode = MODE_HELP;
            break;
        }

        switch(c){
        case 'o': // Output filename
            status_code = argdict_set(dict, ARG_OUTPUT_NAME, optarg);
            break;
        case 'i': // Input filename
            if(argdict_find(dict, ARG_INPUT_NAME, NULL) == 0)
            {
                puts(MULTIPLE_FILES_DETECTED);
                argparse_err = 1;
                break;
            }
            status_code = argdict_set(dict, ARG_INPUT_NAME, optarg);
            break;
        case 'I': // Print file info
            status_code = argdict_set(dict, ARG_PRINT_INFO, "");
            break;
        case 't': // Mode "Triangle"
            if(mode != MODE_NONE)
            {
                puts(MODE_ERR_MSG);
                argparse_err = 1;
                break;
            }
            mode = MODE_TRIANGLE;
            break;
        case 'P': // Points (triangle)
            status_code = argdict_set(dict, ARG_POINTS, optarg);
            break;
        case 'T': // Line thickness (triangle/line)
            status_code = argdict_set(dict, ARG_THICKNESS, optarg);
            break;
        case 'C': // Color (triangle/line)
            status_code = argdict_set(dict, ARG_COLOR, optarg);
            break;
        case 'f': // Fill flag (triangle)
            status_code = argdict_set(dict, ARG_FILL, "");
            break;
        case 'F': // Fill color (triangle)
            status_code = argdict_set(dict, ARG_FILL_COLOR, optarg);
            break;
        case 'b': // Mode "Biggest rectangle search"
            if(mode != MODE_NONE)
            {
                puts(MODE_ERR_MSG);
                argparse_err = 1;
                break;
            }
            mode = MODE_RECT_SEARCH;
            break;
        case 'O': // Old color (rectangle search)
            status_code = argdict_set(dict, ARG_OLD_COLOR, optarg);
            break;
        case 'N': // New color (rectangle search)
            status_code = argdict_set(dict, ARG_NEW_COLOR, optarg);
            break;
        case 'c': // Mode "Collage"
            if(mode != MODE_NONE)
            {
                puts(MODE_ERR_MSG);
                argparse_err = 1;
                break;
            }
            mode = MODE_COLLAGE;
            break;
        case 'X': // Number X (collage)
            status_code = argdict_set(dict, ARG_NUM_X, optarg);
            break;
        case 'Y': // Number Y (collage)
            status_code = argdict_set(dict, ARG_NUM_Y, optarg);
            break;
        case 'l': // Mode "Line"
            if(mode != MODE_NONE)
            {
                puts(MODE_ERR_MSG);
                argparse_err = 1;
                break;
            }
            mode = MODE_LINE;
            break;
        case 'S': // Start (line)
            status_code = argdict_set(dict, ARG_START, optarg);
            break;
        case 'E': // End (line)
            status_code = argdict_set(dict, ARG_END, optarg);
            break;
        case 'z': // Output compression
            status_code = argdict_set(dict, ARG_COMPRESSION, optarg);
            break;
        case 'r':
            if(mode != MODE_NONE)
            {
                puts(MODE_ERR_MSG);
                argparse_err = 1;
                break;
            }
            mode = MODE_ORNAMENT;
            break;
        case '?': // Erroneous argument
            argparse_err = 1;
            break;
        }
    }

    if(status_code)
    {
        argdict_del(dict);
        return status_code;
    }

    if(argparse_err)
    {
        argdict_del(dict);
        return RETCODE_ARG_ERROR;
    }
    
    // Now all options have been parsed, except 'free' arguments
    // at the end of the line
    // It's time to check them out too
    //
    // This program supports only one type of argument - input filename
    // Input filename must be presented everytime except when help called
    int info_flag = argdict_find(dict, ARG_PRINT_INFO, NULL) == 0;
    int input_flag = argdict_find(dict, ARG_INPUT_NAME, NULL) == 0;
    // If filename isn't presented in -i option and mode isn't help
    if(!input_flag &&
       ((mode != MODE_HELP && mode != MODE_NONE) || info_flag) &&
       mode != MODE_HELP)
    {
        // No arguments - that's an error
        if(argc == optind)
        {
            fprintf(stderr, NO_INPUT_FILE);
            argdict_del(dict);
            return RETCODE_ARG_ERROR;
        }
        // Exactly one argument - saving input filename into argdict
        if(argc == optind + 1)
        {
            argdict_set(dict, ARG_INPUT_NAME, argv[optind]);
        }
        // Multiple args - that's an error
        else if(argc > optind + 1)
        {
            fprintf(stderr, MULTIPLE_FILES_DETECTED);
            argdict_del(dict);
            return RETCODE_ARG_ERROR;
        }
    }
    // If we have both -i option and a least one argument
    else if(argc > optind && ((mode != MODE_HELP &&
            mode != MODE_NONE) || info_flag))
    {
        fprintf(stderr, MULTIPLE_FILES_DETECTED);
        argdict_del(dict);
        return RETCODE_ARG_ERROR;
    }
    
    *mode_ptr = mode;
    *argdict_ptr = dict;
    return RETCODE_OK;
}

// Just print help
void argparse_show_help()
{
    puts(HELP_MSG);
}


// This function parse point coordinates from argument string
//
// Arguments:
// s - triangle coordinates in string in format "x.y"
// coords - ptr to int64_t[2] array to store coodinates int,
//          coords have same order: [x, y]
//
// Return:
// 0 = OK
// 1 = Parse error - usually it means bad format
int argparse_point_coords(char *s, int64_t *coords)
{
    regex_t regex;
    regmatch_t match[3];
    // That regex matches "X.Y" in 6 groups
    regcomp(&regex, "^(-?[0-9]*)\\.(-?[0-9]*)$", REG_EXTENDED);
    int success = !regexec(&regex, s, 3, match, 0);
    regfree(&regex);
    
    if(success)
    {
        for(int i = 1; i <= 2; i++)
        {
            size_t str_len = match[i].rm_eo - match[i].rm_so;
            char *substr = (char *)malloc(str_len+1);
            memcpy(substr, s+match[i].rm_so, str_len);
            substr[str_len] = '\0';
            sscanf(substr, "%ld", &(coords[i-1]));
            free(substr);
        }
        return 0;
    }
    return 1;
}


// This function parse triangle coordinates from argument string
//
// Arguments:
// s - triangle coordinates in string in format "x1.y1.x2.y2.x3.y3"
// coords - ptr to int64_t[6] array to store coodinates int,
//          coords have same order: [x1, y1, x2, y2, x3, y3]
//
// Return:
// 0 = OK
// 1 = Parse error - usually it means bad format
int argparse_triangle_coords(char *s, int64_t *coords)
{
    regex_t regex;
    regmatch_t match[7];
    // That regex matches "X1.Y1.X2.Y2.X3.Y3" in 6 groups
    regcomp(&regex, "^(-?[0-9]*)\\.(-?[0-9]*)\\.(-?[0-9]*)\\."
                    "(-?[0-9]*)\\.(-?[0-9]*)\\.(-?[0-9]*)$", REG_EXTENDED);
    int success = !regexec(&regex, s, 7, match, 0);
    regfree(&regex);
    
    if(success)
    {
        for(int i = 1; i <= 6; i++)
        {
            size_t str_len = match[i].rm_eo - match[i].rm_so;
            char *substr = (char *)malloc(str_len+1);
            memcpy(substr, s+match[i].rm_so, str_len);
            substr[str_len] = '\0';
            sscanf(substr, "%ld", &(coords[i-1]));
            free(substr);
        }
        return 0;
    }
    return 1;
}

// This function parse positive integer value from string to uint32_t
// Return:
// 0 = OK
// 1 = Parse error - usually it means bad format
int argparse_pos_int(char *s, uint32_t *pos_int)
{
    regex_t regex;
    // That regex matches exactly one positive integer
    regcomp(&regex, "^[0-9]*$", REG_EXTENDED);
    int success = !regexec(&regex, s, 0, NULL, 0);
    regfree(&regex);
    
    if(success)
    {
        int64_t tmp;
        sscanf(s, "%ld", &tmp);
        if(tmp > 0)
        {
            *pos_int = (uint32_t)tmp;
            return 0;
        }
        else
        {
            return 1;
        }
    }
    return 1;
}


// This function parse integer value from string to uint32_t
// Return:
// 0 = OK
// 1 = Parse error - usually it means bad format
int argparse_int(char *s, int64_t *pos_int)
{
    regex_t regex;
    // That regex matches exactly one positive integer
    regcomp(&regex, "^[0-9]*$", REG_EXTENDED);
    int success = !regexec(&regex, s, 0, NULL, 0);
    regfree(&regex);
    
    if(success)
    {
        int64_t tmp;
        sscanf(s, "%ld", &tmp);
        *pos_int = (uint32_t)tmp;
        return 0;
    }
    return 1;
}


// This function parse color from string in format "R.G.B"
// to PngPixel
// Return:
// 0 = OK
// 1 = Parse error - usually it means bad format
int argparse_color(char *s, Pixel *color)
{
    regex_t regex;
    regmatch_t match[4];
    // That regex matches "R.G.B" in 3 groups
    regcomp(&regex, "^([0-9]{1,3})\\.([0-9]{1,3})\\.([0-9]{1,3})$",
        REG_EXTENDED);
    int success = !regexec(&regex, s, 4, match, 0);
    regfree(&regex);
    
    if(success)
    {
        uint16_t tmp[3];
        for(int i = 1; i <= 3; i++)
        {
            size_t str_len = match[i].rm_eo - match[i].rm_so;
            char *substr = (char *)malloc(str_len+1);
            memcpy(substr, s+match[i].rm_so, str_len);
            substr[str_len] = '\0';
            sscanf(substr, "%hu", &(tmp[i-1]));
            free(substr);
        }
        // Check that values are in correct range 0...255
        if(tmp[0] > 255 || tmp[1] > 255 || tmp[2] > 255)
        {
            return 1;
        }
        // Multiply by 257 to convert 8-bit to 16-bit
        color->r = tmp[0] * 257;
        color->g = tmp[1] * 257;
        color->b = tmp[2] * 257;
        color->a = 0xFFFF;
        return 0;
    }
    return 1;
}


// This function checks and parses all arguments needed for triangle
// drawing task
//
// Arguments:
// argdict - ArgDict object to parse arguments from
//
// Return (as values written to ptrs):
// coords_ptr - int64_t[6] coordinates of triangle vertices in
//              format [x1, y1, x2, y2, x3, y3]
// thickness_ptr - outline thickness for triangle
// color_ptr - outline color for triangle
// fill_ptr - bool flag, fill the triangle or not
// fill_color_ptr - fill color, if fill == 1, else stays unmodified
//
// Return (code):
// Return codes should be handled with handle_error() from "errors.h"
int argparse_mode_triangle(ArgDict *argdict, int64_t *coords_ptr,
                           uint32_t *thickness_ptr, Pixel *color_ptr,
                           uint8_t *fill_ptr, Pixel *fill_color_ptr)
{
    int return_code = RETCODE_OK;
    char *points = NULL;
    char *thickness = NULL;
    char *color = NULL;
    char *fcolor = NULL;
    // Next lines have bool 'not' because 0 is OK (arg found) code
    int points_arg = !argdict_find(argdict, ARG_POINTS, &points);
    int thickness_arg = !argdict_find(argdict, ARG_THICKNESS,
                                      &thickness);
    int color_arg =  !argdict_find(argdict, ARG_COLOR, &color);
    int fill_arg =   !argdict_find(argdict, ARG_FILL, NULL);
    int fcolor_arg = !argdict_find(argdict, ARG_FILL_COLOR, &fcolor);

    if(points_arg && thickness_arg && color_arg &&
       (!fill_arg || (fill_arg && fcolor_arg)))
    {
        int status_points = argparse_triangle_coords(points, coords_ptr);
        int status_thickness = argparse_pos_int(thickness, thickness_ptr);
        int status_color = argparse_color(color, color_ptr);
        *fill_ptr = !argdict_find(argdict, ARG_FILL, NULL);
        int status_fill = 0;
        if(*fill_ptr)
        {
            status_fill = argparse_color(fcolor, fill_color_ptr);
        }
        if(status_points || status_thickness || status_color ||
           (*fill_ptr && status_fill))
        {
            return_code = RETCODE_ARG_ERROR;
            if(status_points)
            {
                fprintf(stderr, WRONG_ARG, "--points", "X1.Y1.X2.Y2.X3.Y3");
            }
            if(status_thickness)
            {
                fprintf(stderr, WRONG_ARG, "--thickness", "<positive int>");
            }
            if(status_color)
            {
                fprintf(stderr, WRONG_ARG, "--color", "R.G.B (0...255)");
            }
            if(*fill_ptr && status_fill)
            {
                fprintf(stderr, WRONG_ARG, "--fill_color", "R.G.B (0...255)");
            }
        }
    }
    else
    {
        return_code = RETCODE_ARG_ERROR;
        if(!points_arg)
        {
            fprintf(stderr, MISSING_ARG, "--points");
        }
        if(!thickness_arg)
        {
            fprintf(stderr, MISSING_ARG, "--thickness");
        }
        if(!color_arg)
        {
            fprintf(stderr, MISSING_ARG, "--color");
        }
        if(fill_arg && !fcolor_arg)
        {
            fprintf(stderr, MISSING_ARG, "--fill_color");
        }
    }

    safe_free(points);
    safe_free(thickness);
    safe_free(color);
    safe_free(fcolor);
    return return_code;
}


// This function checks and parses all arguments needed for triangle
// drawing task
//
// Arguments:
// argdict - ArgDict object to parse arguments from
//
// Return (as values written to ptrs):
// number_x - images along X count
// number_y - images along Y count
//
// Return (code):
// Return codes should be handled with handle_error() from "errors.h"
int argparse_mode_collage(ArgDict *argdict, uint32_t *number_x,
                          uint32_t *number_y)
{
    int return_code = RETCODE_OK;
    char *number_x_s = NULL;
    char *number_y_s = NULL;
    
    // Next lines have bool 'not' because 0 is OK (arg found) code
    int number_x_arg = !argdict_find(argdict, ARG_NUM_X, &number_x_s);
    int number_y_arg = !argdict_find(argdict, ARG_NUM_Y, &number_y_s);
    
    if(number_x_arg && number_y_arg)
    {
        int status_number_x = argparse_pos_int(number_x_s, number_x);
        int status_number_y = argparse_pos_int(number_y_s, number_y);
        
        if(status_number_x || status_number_y)
        {
            return_code = RETCODE_ARG_ERROR;
            if(status_number_x)
            {
                fprintf(stderr, WRONG_ARG, "--number_x", "<positive int>");
            }
            if(status_number_y)
            {
                fprintf(stderr, WRONG_ARG, "--number_y", "<positive int>");
            }
        }
    }
    else
    {
        return_code = RETCODE_ARG_ERROR;
        if(!number_x_arg)
        {
            fprintf(stderr, MISSING_ARG, "--number_x");
        }
        if(!number_y_arg)
        {
            fprintf(stderr, MISSING_ARG, "--number_y");
        }
    }

    safe_free(number_x_s);
    safe_free(number_y_s);
    return return_code;
}


// This function checks and parses all arguments needed for biggest rect
// search task
//
// Arguments:
// argdict - ArgDict object to parse arguments from
//
// Return (as values written to ptrs):
// number_x - images along X count
// number_y - images along Y count
//
// Return (code):
// Return codes should be handled with handle_error() from "errors.h"
int argparse_mode_rect(ArgDict *argdict, Pixel *old_color, Pixel *new_color)
{
    int return_code = RETCODE_OK;
    char *old_color_s = NULL;
    char *new_color_s = NULL;
    
    // Next lines have bool 'not' because 0 is OK (arg found) code
    int old_color_arg = !argdict_find(argdict, ARG_OLD_COLOR, &old_color_s);
    int new_color_arg = !argdict_find(argdict, ARG_NEW_COLOR, &new_color_s);
    
    if(old_color_arg && new_color_arg)
    {
        int status_old_color = argparse_color(old_color_s, old_color);
        int status_new_color = argparse_color(new_color_s, new_color);
        
        if(status_old_color || status_new_color)
        {
            return_code = RETCODE_ARG_ERROR;
            if(status_old_color)
            {
                fprintf(stderr, WRONG_ARG, "--old_color", "R.G.B (0...255)");
            }
            if(status_new_color)
            {
                fprintf(stderr, WRONG_ARG, "--new_color", "R.G.B (0...255)");
            }
        }
    }
    else
    {
        return_code = RETCODE_ARG_ERROR;
        if(!old_color_arg)
        {
            fprintf(stderr, MISSING_ARG, "--old_color");
        }
        if(!new_color_arg)
        {
            fprintf(stderr, MISSING_ARG, "--new_color");
        }
    }

    safe_free(old_color_s);
    safe_free(new_color_s);
    return return_code;
}


// This function checks and parses all arguments needed for line
// drawing task
//
// Arguments:
// argdict - ArgDict object to parse arguments from
//
// Return (as values written to ptrs):
// coords_ptr - int64_t[4] coordinates of line ends in
//              format [x0, y0, x1, y1]
// thickness_ptr - line thickness
// color_ptr - color for line
//
// Return (code):
// Return codes should be handled with handle_error() from "errors.h"
int argparse_mode_line(ArgDict *argdict, int64_t *coords_ptr,
                       uint32_t *thickness_ptr, Pixel *color_ptr)
{
    int return_code = RETCODE_OK;
    char *start = NULL;
    char *end = NULL;
    char *thickness = NULL;
    char *color = NULL;
    // Next lines have bool 'not' because 0 is OK (arg found) code
    int start_arg = !argdict_find(argdict, ARG_START, &start);
    int end_arg = !argdict_find(argdict, ARG_END, &end);
    int thickness_arg = !argdict_find(argdict, ARG_THICKNESS,
                                      &thickness);
    int color_arg =  !argdict_find(argdict, ARG_COLOR, &color);

    if(start_arg && end_arg && thickness_arg && color_arg)
    {
        int status_start = argparse_point_coords(start, coords_ptr);
        int status_end = argparse_point_coords(end, coords_ptr+2);
        int status_thickness = argparse_pos_int(thickness, thickness_ptr);
        int status_color = argparse_color(color, color_ptr);
        if(status_start || status_end || status_thickness || status_color)
        {
            return_code = RETCODE_ARG_ERROR;
            if(status_start)
            {
                fprintf(stderr, WRONG_ARG, "--start", "X.Y");
            }
            if(status_end)
            {
                fprintf(stderr, WRONG_ARG, "--end", "X.Y");
            }
            if(status_thickness)
            {
                fprintf(stderr, WRONG_ARG, "--thickness", "<positive int>");
            }
            if(status_color)
            {
                fprintf(stderr, WRONG_ARG, "--color", "R.G.B (0...255)");
            }
        }
    }
    else
    {
        return_code = RETCODE_ARG_ERROR;
        if(!start_arg)
        {
            fprintf(stderr, MISSING_ARG, "--start");
        }
        if(!end_arg)
        {
            fprintf(stderr, MISSING_ARG, "--end");
        }
        if(!thickness_arg)
        {
            fprintf(stderr, MISSING_ARG, "--thickness");
        }
        if(!color_arg)
        {
            fprintf(stderr, MISSING_ARG, "--color");
        }
    }

    safe_free(start);
    safe_free(end);
    safe_free(thickness);
    safe_free(color);
    return return_code;
}


// This function checks and parses all arguments needed for ornament
// drawing task
//
// Arguments:
// argdict - ArgDict object to parse arguments from
//
// Return (as values written to ptrs):
// thickness_ptr - ornament thickness
// color_ptr - color for the ornament
//
// Return (code):
// Return codes should be handled with handle_error() from "errors.h"
int argparse_mode_ornament(ArgDict *argdict, uint32_t *thickness_ptr, Pixel *color_ptr)
{
    int return_code = RETCODE_OK;
    char *thickness_s = NULL;
    char *color_s = NULL;
    // Next lines have bool 'not' because 0 is OK (arg found) code
    int thickness_arg = !argdict_find(argdict, ARG_THICKNESS,
                                      &thickness_s);
    int color_arg =  !argdict_find(argdict, ARG_COLOR, &color_s);

    if(thickness_arg && color_arg)
    {
        int status_thickness = argparse_pos_int(thickness_s, thickness_ptr);
        int status_color = argparse_color(color_s, color_ptr);
        if(status_thickness || status_color)
        {
            return_code = RETCODE_ARG_ERROR;
            if(status_thickness)
            {
                fprintf(stderr, WRONG_ARG, "--thickness", "<positive int>");
            }
            if(status_color)
            {
                fprintf(stderr, WRONG_ARG, "--color", "R.G.B (0...255)");
            }
        }
    }
    else
    {
        return_code = RETCODE_ARG_ERROR;
        if(!thickness_arg)
        {
            fprintf(stderr, MISSING_ARG, "--thickness");
        }
        if(!color_arg)
        {
            fprintf(stderr, MISSING_ARG, "--color");
        }
    }

    safe_free(thickness_s);
    safe_free(color_s);
    return return_code;
}
