#include <getopt.h>
#include <ctype.h>
#include "image.h"
#include "draw.h"
#include "tools.h"

#define ERR_UNKNOWN_OPRION 300
#define ERR_TOOL_NOT_SELECTED 301
#define ERR_TO_MANY_TOOLS 302

#define ERR_LONG_FILENAME 303
#define ERR_TO_MANY_DOTS 304
#define ERR_INVALID_DOT 305
#define ERR_INVALID_COLOR 306
#define ERR_INVALID_INT 307
#define ERR_INVALID_RANGE 308
#define ERR_TO_MANY_ANGLES 309
#define ERR_INVALID_PATTERN 310
#define ERR_TO_MANY_FILES 311
#define ERR_NO_FILES 312

#define ERR_SPLIT 313
#define ERR_RECTANGLE 314
#define ERR_FRAME 315
#define ERR_TURN 316

#define ERR_WRONG_ARGV 317
#define ERR_FLAG_FILL 318


#define MAX_FILE_NAME 255
#define MAX_DOTS_COUNT 2


void raise_error(int error, int val)
{
     char error_text[100][1000] = {
        "The option is unknown or a required argument is not specified",
        "Use first one of this tools --split (-s), --rect (-r), --ornament (-o), --rotate (-r)",
        "Select one of the tools (two or more are specified)",
        "Filename is too long",
        "Too many dots (points) were passed as options",
        "Invalid dot (point). Write 2 unsigned integers separated by commas (without spaces)",
        "Invalid color. Write color in RGB: 3 unsigned integers [0;255] separated by commas (without spaces).",
        "Failed to convert string to number",
        "The number should be in the range from 1 to the width or height of the image",
        "Too many angles were passed as options",
        "Invalid pattern number",
        "Too many files",
        "Need input file",
        "Invalid arguments to split",
        "Invalid arguments to rectangle",
        "Invalid arguments to frame",
        "Invalid arguments to rotate",
        "Two input files are specified or an extra unknown argv argument is specified",
        "Missing --fill flag"
    };
    
    if (error) {
        if (300 <= error <= 399) {
            if (val > 0) {
                fprintf(stderr, "-%c: %s. Use -h or --help\n", val, error_text[error-300]);
            } else {
                fprintf(stderr, "%s. Use -h or --help\n", error_text[error-300]);
            }
        }
        exit(45);
    }
}

// Является ли строка числом
int isNumeric(char *str)
{
    if (str == NULL)
        return 0;
    int i = 0;
    while (str[i] != '\0' && (isdigit(str[i]) || (str[0] == '-'))) {
        if (!(isdigit(str[i]) || (str[0] == '-'))) {
            return 0;
        }
        i++;
    }
    return 1;
}

// Преобразование строки в структуру point
point *str_to_point(char *str)
{
    if (str == NULL) 
        return NULL;
    int count, x, y;
    count = sscanf(str, "%d.%d", &x, &y);
    if (count != 2) 
        return NULL;
    if (x < 0 || y < 0) 
        return NULL;
    return init_point(x, y);
}

// Преобразование строки в структуру color
color *str_to_color(char *str)
{
    if (str == NULL) 
        return NULL;
    int count, r, g, b;
    count = sscanf(str, "%d.%d.%d", &r, &g, &b);
    if (count != 3) 
        return NULL;
    return init_color(r, g, b);
}

int main(int argc, char *argv[])
{
    const char* short_options = "hsofti:n:m:c:p:a:";
    const struct option long_options[] = {
        { "help", no_argument, NULL, 'h' },
        { "split", no_argument, NULL, 'S' },
        { "rect", no_argument, NULL, 'R' },
        { "ornament", no_argument, NULL, 'F' },
        { "rotate", no_argument, NULL, 'T' },
        { "input", required_argument, NULL, 'i'},
        { "output", required_argument, NULL, 'o'},
        { "number_x", required_argument, NULL, 'n'},
        { "number_y", required_argument, NULL, 'm'},
        { "color", required_argument, NULL, 'c'},
        { "fill", no_argument, NULL, 'f'},
        { "fill_color", required_argument, NULL, 'G'},  
        { "pattern", required_argument, NULL, 'p'},
        { "angle", required_argument, NULL, 'a'},
        { "count", required_argument, NULL, 'N'},
        { "thickness", required_argument, NULL, 'W'},
        { "left_up", required_argument, NULL, 'L'},
        { "right_down", required_argument, NULL, 'D'},   
        { "info", required_argument, NULL, 'H'}, 
        { "compress", no_argument, NULL, 'C'},
        { "num", required_argument, NULL, 'Q'},
        { NULL, 0, NULL, 0 }
    };
	
    int val;
	int option_index = -1; // индекс текущей опции
    int options_count = 0; // кол-во обработанных опций

    int count = -1;
    int thickness = -1; // толщина линии
    int tool = 0; // 1 - split, 2 - rectangle, 3 - frame, 4 - turn
    int input_flag = 0; // был ли указан входной файл
    char input_file[MAX_FILE_NAME + 1]; // путь к входному файлу
    int output_flag = 0; // был ли указан выходной файл
    char output_file[MAX_FILE_NAME + 1]; // путь к выходному файлу
    point *new_dot = NULL; // указатель на точку
    point *dots[MAX_DOTS_COUNT]; // массив указателей на точки
    int dots_count = 0; // кол-во точек
    color *clr = NULL; // цвет
    int number;
    int n = -1; // число разделений по горизонтали
    int m = -1; // число разделений по вертикали
    // int width = -1; // ширина
    int flag_angle = 0; // был ли указан угол поворота
    int angle = -1; // угол поворота
    int pattern = 0; // узор для рамки
    char *pattern_str = NULL;
    int fill = 0;
    int flag_fill_color = 0;
    color *fill_color = NULL; // заполнение цветом
    point *left;
    point *right;
    int N = -1;

    int error = 0;
    while ((val = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
        switch (val) {
            // Справка (help)
            case 'h':
                puts(
                    "Course work for option 5.11, created by Aleksandr Volkov\n\n"
                    "1) Split. Divides images into NxM parts.\n"
                    "Accepts the input numbers N and M, the color and thickness of the stroke.\n"
                    "Key: --split or -s\n" 
                    "Parameter Keys:\n"
                    "\t--number_x or -n: unsigned integer, range [1; width of image]\n"
                    "\t--number_y or -m: unsigned integer, range [1; height of image]\n"
                    "\t--thickness: unsigned integer, >= 1\n"
                    "\t--color or -c: RGB, 3 unsigned integers, range [0; 255]\n\n"
                    
                    "2) Rectangle. Draws a rectangle with an outline and fill.\n"
                    "Accepts two dots, fill color (optinal), the color and thickness of the stroke.\n"
                    "Key: --rect or -r\n" 
                    "Parameter Keys:\n"
                    "\t--left_up: 2 unsigned integers through the point, >= 0\n"
                    "\t--right_down: 2 unsigned integers through the point, >= 0\n"
                    "\t--fill: true or false\n"
                    "\t--fill_color:  RGB, 3 unsigned integers, range [0; 255]\n"
                    "\t--color or -c: RGB, 3 unsigned integers, range [0; 255]\n\n"
                    
                    "3) Ornament. Draws a frame around the image.\n"
                    "Accepts pattern number, the color and thickness of the stroke.\n"
                    "Key: --ornament or -o\n" 
                    "Parameter Keys:\n"
                    "\t--pattern or -p: rectangle or circle or semicircles\n"
                    "\t--thickness: unsigned integer, >= 1\n"
                    "\t--count: unsigned integer, >= 1\n"
                    "\t--color or -c: RGB, 3 unsigned integers, range [0; 255]\n\n"

                    "4) Rotate. Rotates part of the image by the specified number of degrees\n"
                    "Accepts two dots and angle (in degrees).\n"
                    "Key: --rotate or -r\n" 
                    "Parameter Keys:\n"
                    "\t--left_up: 2 unsigned integers through the point, >= 0\n"
                    "\t--right_down: 2 unsigned integers through the point, >= 0\n"
                    "\t--angle or -a: integer\n\n"
                    
                    "Also, all functions require an input file,\n"
                    "which can be specified via the --input or -i key.\n"
                    "The output file is defined by a similar flag --output or -o.\n"
                );

                exit(0);
                break;
            
            case 'H': // --info
                if (strlen(optarg) >= MAX_FILE_NAME) {
                    error = ERR_LONG_FILENAME;
                    break;
                }
                strncpy(input_file, optarg, MAX_FILE_NAME);
                
                image *img = load_image(input_file);
                raise_error(!img, -1);

                printf("Image Information:\n");
                printf("Path: %s\n", img->path);
                printf("Width: %u\n", img->width);
                printf("Height: %u\n", img->height);
                printf("Color Type: %u\n", img->color_type);
                printf("Bit Depth: %u\n", img->bit_depth);
                input_flag = 1;
                exit(0);
                break;

            // Выбор инструмента
            case 'S': // --split or -s
                if (tool) {
                    error = ERR_TO_MANY_TOOLS;
                    break;
                }
                tool = 1;
                break;

            case 'R': // --rect or -r
                if (tool) {
                    error = ERR_TO_MANY_TOOLS;
                    break;
                }
                tool = 2;
                break;

            case 'F': // --ornament or -o
                if (tool) {
                    error = ERR_TO_MANY_TOOLS;
                    break;
                }
                tool = 3;
                break;

            case 'T': // --rotate or -t
                if (tool) {
                    error = ERR_TO_MANY_TOOLS;
                    break;
                }
                tool = 4;
                break;       

            case 'C': // --rotate or -t
                if (tool) {
                    error = ERR_TO_MANY_TOOLS;
                    break;
                }
                tool = 5;
                break;          

            // Ввод параметров инструментов
            case 'i': // --input or -i
                if (input_flag) {
                    error = ERR_TO_MANY_FILES; 
                    break;
                }

                if (strlen(optarg) >= MAX_FILE_NAME) {
                    error = ERR_LONG_FILENAME;
                    break;
                }
                input_flag = 1;
                strncpy(input_file, optarg, MAX_FILE_NAME);
                break;

            case 'o': // --output or -o
                if (output_flag) {
                    error = ERR_TO_MANY_FILES; 
                    break;
                }

                if (strlen(optarg) >= MAX_FILE_NAME) {
                    error = ERR_LONG_FILENAME;
                    break;
                }
                output_flag = 1;
                strncpy(output_file, optarg, MAX_FILE_NAME);
                break;

            case 'c': // --color or -c
                clr = str_to_color(optarg);
                if (!clr) {
                    error = ERR_INVALID_COLOR; 
                    break;
                }
                break;


            case 'f': // --fill
                fill = 1; 
                break;

            case 'G': // --fill_color
                fill_color = str_to_color(optarg);
                if (!fill_color) {
                    error = ERR_INVALID_COLOR; 
                    break;
                }
                flag_fill_color = 1;
                break;

            case 'n': // --number_x
                if (!isNumeric(optarg)) {
                    error = ERR_INVALID_INT; 
                    break;
                }

                number = atoi(optarg);
                if (1 > number) {
                    error = ERR_INVALID_RANGE; 
                    break;
                }
                n = number;
                break;

            case 'Q': // --num
                if (!isNumeric(optarg)) {
                    error = ERR_INVALID_INT; 
                    break;
                }

                number = atoi(optarg);
                if (1 >= number) {
                    error = ERR_INVALID_RANGE; 
                    break;
                }
                N = number;
                break;

            case 'm': // --number_y
                if (!isNumeric(optarg)) {
                    error = ERR_INVALID_INT; 
                    break;
                }

                number = atoi(optarg);
                if (1 > number) {
                    error = ERR_INVALID_RANGE; 
                    break;
                }
                m = number;
                break;

            case 'a': // --angle or -a
                if (!isNumeric(optarg)) {
                    error = ERR_INVALID_INT; 
                    break;
                }
                
                if (flag_angle) {
                    error = ERR_TO_MANY_ANGLES; 
                    break;
                }
                number = atoi(optarg);
                angle = number;
                flag_angle = 1;
                break;

            case 'p': // --pattern or -p
                pattern_str = optarg;
                if (strcmp(pattern_str, "rectangle") != 0 && strcmp(pattern_str, "circle") != 0 && strcmp(pattern_str, "semicircles") != 0) {
                    error = ERR_INVALID_PATTERN; 
                    break;
                }

                if (strcmp(pattern_str, "rectangle") == 0) {
                    pattern = 1;
                } else if (strcmp(pattern_str, "circle") == 0) {
                    pattern = 2;
                } else if (strcmp(pattern_str, "semicircles") == 0) {
                    pattern = 3;
                }

                break;
            
            case 'N': // --count
                if (!isNumeric(optarg)) {
                    error = ERR_INVALID_INT; 
                    break;
                }

                number = atoi(optarg);
                if (1 > number) {
                    error = ERR_INVALID_RANGE; 
                    break;
                }
                count = number;
                break;

            case 'W': // --thickness
                if (!isNumeric(optarg)) {
                    error = ERR_INVALID_INT; 
                    break;
                }

                number = atoi(optarg);
                if (1 > number) {
                    error = ERR_INVALID_RANGE; 
                    break;
                }
                thickness = number;
                break;

            case 'L': // --left_up
                if (dots_count >= MAX_DOTS_COUNT) {
                    error = ERR_TO_MANY_DOTS; 
                    break;
                }

                new_dot = str_to_point(optarg);
                if (!new_dot) {
                    error = ERR_INVALID_DOT;
                    break;
                }
                dots[dots_count++] = new_dot;
                left = new_dot;
                break;

            case 'D': // --right_down
                if (dots_count >= MAX_DOTS_COUNT) {
                    error = ERR_TO_MANY_DOTS; 
                    break;
                }

                new_dot = str_to_point(optarg);
                if (!new_dot) {
                    error = ERR_INVALID_DOT;
                    break;
                }
                dots[dots_count++] = new_dot;
                right = new_dot;
                break;
            
            // Неизвестный флаг
            case '?': 
            default: {
                error = ERR_UNKNOWN_OPRION;
                break;
            }
        }
        
        if (error)
            break;
        option_index = -1;
        options_count++;
    }

    options_count -= output_flag + input_flag + (tool > 0);

    raise_error(error, val);
    if (tool == 0)
        error = ERR_TOOL_NOT_SELECTED;

    if (optind < argc){
        if (!input_flag) {
            if (strlen(argv[argc - 1]) > MAX_FILE_NAME) {
                error = ERR_LONG_FILENAME;
            } else {
                input_flag = 1;
                strncpy(input_file, argv[argc - 1], MAX_FILE_NAME);
            }
        } else {
            error = ERR_WRONG_ARGV;
        }
    }
    if (!input_flag) {
        error = ERR_NO_FILES;
    }
    raise_error(error, -1);

    image *img = load_image(input_file);
    raise_error(!img, -1);

    image *out = NULL;
    switch (tool) {
        case 1:
            //SPLIT
            if ((n == -1) || (m == -1) || (clr == NULL) || (thickness < 0) || (options_count != 4)) {
                error = ERR_SPLIT;
                break;
            }

            out = split(img, n, m, thickness, clr);
            if (!out) {
                error = ERR_SPLIT; 
                break;
            }
            break;
            
        case 2:
            //RECTANGLE
            if ((dots_count != 2) || (clr == NULL) || (thickness < 0) || (options_count < 3) || (options_count > 6)) {
                error = ERR_RECTANGLE;
                break;
            }

            if (left->y > img->height && right->y > img->height) {
                out = img;
                break;
            }

            if (left->x > img->width && right->x > img->width) {
                out = img;
                break;
            }

            if (left->x > right->x) {
                double tmp = left->x;
                left->x = right->x;
                right->x = tmp;
            }

            if (left->y > right->y) {
                double tmp = left->y;
                left->y = right->y;
                right->y = tmp;
            }

            if (fill == 1 && flag_fill_color == 1) {
                out = rectangle(init_selection(img, left, right), thickness, clr, fill_color);
            } else if (fill == 0 && flag_fill_color == 0) {
                out = rectangle(init_selection(img, left, right), thickness, clr, NULL);
            } else if (fill == 1 && flag_fill_color == 0) {
                error = ERR_RECTANGLE;
            } else if (fill == 0 && flag_fill_color == 1) {
                out = rectangle(init_selection(img, left, right), thickness, clr, NULL);
            }
            
            if (!out) {
                error = ERR_RECTANGLE; 
                break;
            }
            break;

        case 3:
            //FRAME
            if ((pattern < 0) || (clr == NULL) || (count < 0) || (thickness < 0) || (options_count > 4)) {
                error = ERR_FRAME;
                break;
            }

            out = frame(img, clr, thickness, count, pattern);
            
            if (!out) {
                error = ERR_FRAME; 
                break;
            }
            break;

        case 4:
            //ROTATE
            if ((dots_count != 2) || (flag_angle == 0) || (options_count != 3)) {
                error = ERR_TURN;
                break;
            }

            out = rotate(img, init_selection(img, left, right), angle);   
            if (!out) {
                error = ERR_TURN; 
                break;
            }
            break;

        case 5:
            //COMPRESS
            if ((N == -1) || (options_count != 1)) {
                error = ERR_SPLIT;
                break;
                exit(45);
            }

            out = compress(img, N);
            if (!out) {
                error = ERR_SPLIT; 
                break;
            }
            break;

        default:
            error = ERR_TOOL_NOT_SELECTED;
            exit(45);
            break;
    }

    raise_error(error, -1);
    if (!output_flag) {
        error = save_image(out, input_file);
    } else {
        error = save_image(out, output_file);
    }
    raise_error(error, -1);
    return 0;
}
