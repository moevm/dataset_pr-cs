#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pngdata.h"
#include "pngio.h"
#include "pngmnp.h"

#define COURSE_WORK_INFO "Course work for option 5.11, created by Petr Pimenov.\n"
#define HELP                                                                                                           \
    "Usage:\n    --split: Split the image into N*M parts.\n    Parameters:\n        --number_x: Number of parts "      \
    "along the X axis.\n        --number_y: Number of parts along the Y axis.\n        --thickness: Line "             \
    "thickness.\n        --color: Line color.\n        --input (-i): Input file path.\n        --output (-o): Output " \
    "file path.\n    Example:\n        ./cw --split --number_x 2 --number_y 3 --thickness 3 --color 12.34.56 -i "      \
    "input.png -o output.png\n\n    --rect: Draw a rectangle.\n    Parameters:\n        --left_up: Coordinates of "    \
    "the upper left corner.\n        --right_down: Coordinates of the lower right corner.\n        --thickness: Line " \
    "thickness.\n        --color: Line color.\n        --fill: Is rectangle filled?\n        "                         \
    "--fill_color: Fill color (if rectangle is filled).\n        --input (-i): Input file path.\n        --output "    \
    "(-o): Output file path.\n    Example:\n        ./cw --rect --left_up 10.10 --right_down 20.20 --thickness 1 "     \
    "--color 12.34.56 --fill --fill_color 77.88.99 -i input.png -o output.png\n\n    --ornament: Make a frame "        \
    "in the form of a pattern.\n    Parameters:\n        --pattern: [rectangle/circles/semicircles] Ornament "         \
    "pattern.\n        --color: Ornament color.\n        --thickness: Thickness (if needed).\n        --count: Count " \
    "(if needed).\n        --input (-i): Input file path.\n        --output (-o): Output file path.\n    Example:\n  " \
    "      ./cw --ornament --pattern rectangle --color 12.34.56 --thickness 10 --count 5 -i input.png -o "             \
    "output.png\n\n    "                                                                                               \
    "--rotate: Rotate an image part by 90/180/270 degrees\n    Parameters:\n        --left_up: Coordinates of the "    \
    "upper left corner.\n        --right_down: Coordinates of the lower right corner.\n        --angle: [90/180/270] " \
    "Rotation angle.\n        --input (-i): Input file path.\n        --output (-o): Output file path.\n    "          \
    "Example:\n        ./cw --rotate --left_up 10.10 --right_down 20.20 --angle 90 -i input.png -o output.png\n\n    " \
    "--info: Print image data.\n    Parameters:\n        --input (-i): Input file path.\n    Example:\n        ./cw "  \
    "--info -i input.png\n\n    --help (-h): Print usage data.\n    Parameters:\n        No parameters.\n    "         \
    "Example:\n        ./cw --help\n"
#define IMAGE_INFO          "Width: %d\nHeight: %d\nColor type: %d\nBit depth: %d\nNumber of passes for image interlacing: %d\n"
#define DEFAULT_OUTPUT_FILE "out.png"

typedef struct {
    int argc;
    int* function;
    char* input_path;
    char* output_path;
    int* x0;
    int* y0;
    int* x1;
    int* y1;
    color_t* color;
    int* thickness;
    int* fill;
    color_t* fill_color;
    int* pattern;
    int* count;
    int* angle;
    int* number_x;
    int* number_y;
} parameters_t;

int* copy_int(int source);
char* copy_string(char* source);
int parse_int(int** parameter, int* argc);
int parse_function(int** parameter, int* argc, int function);
int parse_string(char** parameter, int* argc);
int parse_color(color_t** parameter, int* argc);
int parse_coordinates(int** parameter_x, int** parameter_y, int* argc);
int parse_bool(int** parameter, int* argc);
int parse_pattern(int** parameter, int* argc);
int process(parameters_t* parameters_t);
int function1(image_t* image, int number_x, int number_y, int thickness, color_t* color);
int function2(image_t* image, int x0, int y0, int x1, int y1, int thickness, color_t* color, color_t* fill_color);
int function3(image_t* image, int pattern, color_t* color, int thickness, int count);
int function4(image_t* image, int x0, int y0, int x1, int y1, int angle);
int function5(image_t* image, color_t* color, int thickness);
int function99(image_t* image);
int function100();
void free_parameters(parameters_t* parameters);

int
main(int argc, char* argv[]) {
    printf(COURSE_WORK_INFO);

    parameters_t p = {};
    parameters_t* parameters = &p;

    opterr = 0;
    char optstr[] = "hi:o:";
    struct option options[] = {{"help", 0, NULL, 'h'},
                               {"input", 1, NULL, 'i'},
                               {"output", 1, NULL, 'o'},
                               {"split", 0, NULL, 300},
                               {"number_x", 1, NULL, 301},
                               {"number_y", 1, NULL, 302},
                               {"thickness", 1, NULL, 303},
                               {"color", 1, NULL, 304},
                               {"rect", 0, NULL, 305},
                               {"left_up", 1, NULL, 306},
                               {"right_down", 1, NULL, 307},
                               {"fill", 0, NULL, 308},
                               {"fill_color", 1, NULL, 309},
                               {"ornament", 0, NULL, 310},
                               {"pattern", 1, NULL, 311},
                               {"count", 1, NULL, 312},
                               {"rotate", 0, NULL, 313},
                               {"angle", 1, NULL, 314},
                               {"info", 0, NULL, 315},
                               {"outside_ornament", 0, NULL, 316},
                               {NULL, 0, NULL, 0}};

    int getopt_result;
    int success = 1;

    while ((getopt_result = getopt_long(argc, argv, optstr, options, NULL)) != -1 && success) {
        switch (getopt_result) {
            case 'h': {
                success = parse_function(&parameters->function, &parameters->argc, 100);
                break;
            }
            case 'i': {
                success = parse_string(&parameters->input_path, &parameters->argc);
                break;
            }
            case 'o': {
                success = parse_string(&parameters->output_path, &parameters->argc);
                break;
            }
            case 300: {
                success = parse_function(&parameters->function, &parameters->argc, 1);
                break;
            }
            case 301: {
                success = parse_int(&parameters->number_x, &parameters->argc);
                break;
            }
            case 302: {
                success = parse_int(&parameters->number_y, &parameters->argc);
                break;
            }
            case 303: {
                success = parse_int(&parameters->thickness, &parameters->argc);
                break;
            }
            case 304: {
                success = parse_color(&parameters->color, &parameters->argc);
                break;
            }
            case 305: {
                success = parse_function(&parameters->function, &parameters->argc, 2);
                break;
            }
            case 306: {
                success = parse_coordinates(&parameters->x0, &parameters->y0, &parameters->argc);
                break;
            }
            case 307: {
                success = parse_coordinates(&parameters->x1, &parameters->y1, &parameters->argc);
                break;
            }
            case 308: {
                success = parse_bool(&parameters->fill, &parameters->argc);
                break;
            }
            case 309: {
                success = parse_color(&parameters->fill_color, &parameters->argc);
                break;
            }
            case 310: {
                success = parse_function(&parameters->function, &parameters->argc, 3);
                break;
            }
            case 311: {
                success = parse_pattern(&parameters->pattern, &parameters->argc);
                break;
            }
            case 312: {
                success = parse_int(&parameters->count, &parameters->argc);
                break;
            }
            case 313: {
                success = parse_function(&parameters->function, &parameters->argc, 4);
                break;
            }
            case 314: {
                success = parse_int(&parameters->angle, &parameters->argc);
                break;
            }
            case 315: {
                success = parse_function(&parameters->function, &parameters->argc, 99);
                break;
            }
            case 316: {
                success = parse_function(&parameters->function, &parameters->argc, 5);
                break;
            }
            case '?':
            default: {
                success = 0;
                printf("Error: Unknown option or missing arguments.\n");
                break;
            };
        }
    }
    if (parameters->input_path == NULL && optind == argc - 1) {
        parameters->input_path = copy_string(argv[argc - 1]);
        parameters->argc += 1;
    }
    int result = 0;
    if (success) {
        result = process(parameters);
    } else {
        result = 40;
    }
    free_parameters(parameters);
    return result;
}

int*
copy_int(int source) {
    int* new_int = (int*)malloc(1 * sizeof(int));
    *new_int = source;
    return new_int;
}

char*
copy_string(char* source) {
    char* new_string = (char*)calloc(strlen(source) + 1, sizeof(char));
    strncpy(new_string, source, strlen(source) + 1);
    return new_string;
}

int
parse_int(int** parameter, int* argc) {
    if (parameter == NULL || argc == NULL) {
        printf("Error: pointer to parameter or argc is NULL.\n");
        return 0;
    }
    if (*parameter == NULL) {
        int parsed = atoi(optarg);
        if (parsed == 0 && strcmp(optarg, "0") != 0) {
            printf("Error: Could not parse an int.\n");
            return 0;
        }
        *parameter = copy_int(parsed);
        *argc += 1;
    } else {
        printf("Error: Extra option.\n");
        return 0;
    }
    return 1;
}

int
parse_function(int** parameter, int* argc, int function) {
    if (parameter == NULL || argc == NULL) {
        printf("Error: pointer to parameter or argc is NULL.\n");
        return 0;
    }
    if (*parameter == NULL) {
        *parameter = copy_int(function);
        *argc += 1;
    } else {
        printf("Error: Extra option.\n");
        return 0;
    }
    return 1;
}

int
parse_string(char** parameter, int* argc) {
    if (parameter == NULL || argc == NULL) {
        printf("Error: pointer to parameter or argc is NULL.\n");
        return 0;
    }
    if (*parameter == NULL) {
        *parameter = copy_string(optarg);
        *argc += 1;
    } else {
        printf("Error: Extra option.\n");
        return 0;
    }
    return 1;
}

int
parse_color(color_t** parameter, int* argc) {
    if (parameter == NULL || argc == NULL) {
        printf("Error: pointer to parameter or argc is NULL.\n");
        return 0;
    }
    if (*parameter == NULL) {
        int r = 0, g = 0, b = 0;
        int count = sscanf(optarg, "%d.%d.%d", &r, &g, &b);
        if (count != 3 || r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) {
            printf("Error: Could not parse a color.\n");
            return 0;
        }
        *parameter = create_color((png_byte)r, (png_byte)g, (png_byte)b);
        *argc += 1;
    } else {
        printf("Error: Extra option.\n");
        return 0;
    }
    return 1;
}

int
parse_coordinates(int** parameter_x, int** parameter_y, int* argc) {
    if (parameter_x == NULL || parameter_y == NULL || argc == NULL) {
        printf("Error: pointer to parameter or argc is NULL.\n");
        return 0;
    }
    if (*parameter_x == NULL && *parameter_y == NULL) {
        int x = 0, y = 0;
        int count = sscanf(optarg, "%d.%d", &x, &y);
        if (count != 2) {
            printf("Error: Could not parse coordinates.\n");
            return 0;
        }
        *parameter_x = copy_int(x);
        *parameter_y = copy_int(y);
        *argc += 2;
    } else {
        printf("Error: Extra option.\n");
        return 0;
    }
    return 1;
}

int
parse_bool(int** parameter, int* argc) {
    if (parameter == NULL || argc == NULL) {
        printf("Error: pointer to parameter or argc is NULL.\n");
        return 0;
    }
    if (*parameter == NULL) {
        *parameter = copy_int(1);
        *argc += 1;
    } else {
        printf("Error: Extra option.\n");
        return 0;
    }
    return 1;
}

int
parse_pattern(int** parameter, int* argc) {
    if (parameter == NULL || argc == NULL) {
        printf("Error: pointer to parameter or argc is NULL.\n");
        return 0;
    }
    if (*parameter == NULL) {
        if (!strcmp(optarg, "rectangle")) {
            *parameter = copy_int(1);
        } else if (!(strcmp(optarg, "circle"))) {
            *parameter = copy_int(2);
        } else if (!(strcmp(optarg, "semicircles"))) {
            *parameter = copy_int(3);
        } else {
            printf("Error: Could not parse an argument.\n");
            return 0;
        }
        *argc += 1;
    } else {
        printf("Error: Extra option.\n");
        return 0;
    }
    return 1;
}

int
process(parameters_t* parameters) {
    int result = 0;
    if (parameters->function == NULL) {
        printf("Error: Function parameter not found.\n");
        return 40;
    }

    int function = *parameters->function;
    if (function == 100) {
        if (parameters->argc == 1) {
            result = function100();
            return result;
        } else {
            printf("Error: Extra option.\n");
            return 40;
        }
    }

    if (parameters->input_path == NULL) {
        printf("Error: Input file path not found.\n");
        return 40;
    }

    image_t i = {};
    image_t* image = &i;
    result = read_png_file(parameters->input_path, image);
    if (result != 0) {
        return result;
    }

    if (function == 99) {
        if (parameters->argc == 2) {
            result = function99(image);
            free_canvas(image->canvas);
            return result;
        } else {
            printf("Error: Extra option.\n");
            return 40;
        }
    }

    if (parameters->output_path == NULL) {
        parameters->output_path = copy_string(DEFAULT_OUTPUT_FILE);
        parameters->argc += 1;
    }

    if (strcmp(parameters->input_path, parameters->output_path) == 0) {
        printf("Error: Input file is the same as the output file.\n");
        free_canvas(image->canvas);
        return 40;
    }

    if (function == 1) {
        if (parameters->argc == 7 && parameters->number_x && parameters->number_y && parameters->thickness
            && parameters->color) {
            result = function1(image, *parameters->number_x, *parameters->number_y, *parameters->thickness,
                               parameters->color);
        } else {
            printf("Error: Missing or extra options.\n");
            free_canvas(image->canvas);
            return 40;
        }
    } else if (function == 2) {
        if (!(parameters->x0 && parameters->y0 && parameters->x1 && parameters->y1 && parameters->thickness
              && parameters->color)) {
            printf("Error: Missing or extra options.\n");
            free_canvas(image->canvas);
            return 40;
        }
        if (parameters->argc == 9 && !parameters->fill && !parameters->fill_color) {
            result = function2(image, *parameters->x0, *parameters->y0, *parameters->x1, *parameters->y1,
                               *parameters->thickness, parameters->color, NULL);
        } else if (parameters->argc == 10 && !parameters->fill && parameters->fill_color) {
            result = function2(image, *parameters->x0, *parameters->y0, *parameters->x1, *parameters->y1,
                               *parameters->thickness, parameters->color, NULL);
        } else if (parameters->argc == 10 && parameters->fill && !parameters->fill_color) {
            printf("Error: Missing or extra options.\n");
            free_canvas(image->canvas);
            return 40;
        } else if (parameters->argc == 11 && parameters->fill && parameters->fill_color) {
            result = function2(image, *parameters->x0, *parameters->y0, *parameters->x1, *parameters->y1,
                               *parameters->thickness, parameters->color, parameters->fill_color);
        } else {
            printf("Error: Missing or extra options.\n");
            free_canvas(image->canvas);
            return 40;
        }
    } else if (function == 3) {
        if (parameters->argc == 7 && parameters->pattern && parameters->color && parameters->thickness
            && parameters->count) {
            result = function3(image, *parameters->pattern, parameters->color, *parameters->thickness,
                               *parameters->count);
        } else {
            printf("Error: Missing or extra options.\n");
            free_canvas(image->canvas);
            return 40;
        }
    } else if (function == 4) {
        if (parameters->argc == 8 && parameters->x0 && parameters->y0 && parameters->x1 && parameters->y1
            && parameters->angle) {
            result = function4(image, *parameters->x0, *parameters->y0, *parameters->x1, *parameters->y1,
                               *parameters->angle);
        } else {
            printf("Error: Missing or extra options.\n");
            free_canvas(image->canvas);
            return 40;
        }
    } else if (function == 5) {
        if (parameters->argc == 5 && parameters->thickness && parameters->color) {
            result = function5(image, parameters->color, *parameters->thickness);
        } else {
            printf("Error: Missing or extra options.\n");
            free_canvas(image->canvas);
            return 40;
        }
    }

    result = write_png_file(parameters->output_path, image);
    free_canvas(image->canvas);
    return result;
}

int
function1(image_t* image, int number_x, int number_y, int thickness, color_t* color) {
    return split(image->canvas, color, number_x, number_y, thickness);
}

int
function2(image_t* image, int x0, int y0, int x1, int y1, int thickness, color_t* color, color_t* fill_color) {
    return draw_rectangle(image->canvas, color, fill_color, x0, y0, x1, y1, thickness);
}

int
function3(image_t* image, int pattern, color_t* color, int thickness, int count) {
    return ornament(image->canvas, color, pattern, count, thickness);
}

int
function4(image_t* image, int x0, int y0, int x1, int y1, int angle) {
    return rotate(image->canvas, x0, y0, x1, y1, angle);
}

int
function5(image_t* image, color_t* color, int thickness) {
    return outside_ornament(image, color, thickness);
}

int
function99(image_t* image) {
    printf(IMAGE_INFO, image->canvas->width, image->canvas->height, image->color_type, image->bit_depth,
           image->number_of_passes);
    return 0;
}

int
function100() {
    printf(HELP);
    return 0;
}

void
free_parameters(parameters_t* parameters) {
    free(parameters->function);
    free(parameters->input_path);
    free(parameters->output_path);
    free(parameters->x0);
    free(parameters->y0);
    free(parameters->x1);
    free(parameters->y1);
    free(parameters->color);
    free(parameters->thickness);
    free(parameters->fill);
    free(parameters->fill_color);
    free(parameters->pattern);
    free(parameters->count);
    free(parameters->angle);
    free(parameters->number_x);
    free(parameters->number_y);
}