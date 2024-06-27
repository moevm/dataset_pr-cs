#ifndef MAIN_HEADER
#define MAIN_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include <string.h>
#include <getopt.h>
#include <math.h>

#define MAX_COLOR_COMPONENT 4
#define PNG_SIGNATURE_BYTES 8
#define EXIT_CODE 46
#define ERROR_MESSAGE "Ошибка: не удалось прочитать файл"
#define ERROR_READ "Ошибка: не удалось создать структуру для чтения формата PNG"
#define ERROR_INFORMATION "Ошибка: не удалось создать информационную структуру PNG"
#define ERROR_OPEN "Ошибка: не удается открыть файл  для записи"
#define ERROR_WRITE "Ошибка: не удалось создать информационную структуру PNG"
#define ERROR_PRUNING "Ошибка: обрезка не возможна!"
#define ERROR_SIZE "Ошибка: размеры итогового изображения равны 0"


#define SHORT_OPTIONS "o:i:ls:e:c:t:fIC:r:TL:R:hmM:y:"

#define OPTION_OUTPUT "output", required_argument , NULL, 'o'
#define SHORT_FLAG_OUTPUT 'o'
#define OPTION_INPUT "input", required_argument , NULL, 'i'
#define SHORT_FLAG_INPUT 'i'
#define OPTION_LINE "line", no_argument, NULL, 'l'
#define SHORT_FLAG_LINE 'l'
#define OPTION_START "start", required_argument, NULL, 's'
#define SHORT_FLAG_START 's'
#define OPTION_END "end", required_argument, NULL, 'e'
#define SHORT_FLAG_END 'e'
#define OPTION_COLOR "color", required_argument, NULL, 'c'
#define SHORT_FLAG_COLOR 'c'
#define OPTION_THICKNESS "thickness", required_argument, NULL, 't'
#define SHORT_FLAG_THICKNESS 't'
#define OPTION_INFO "info", no_argument, NULL, 'f'
#define SHORT_FLAG_INFO 'f'
#define OPTION_INVERSE_CIRCLE "inverse_circle", no_argument, NULL, 'I'
#define SHORT_FLAG_INVERSE_CIRCLE 'I'
#define OPTION_CENTER "center", required_argument, NULL, 'C'
#define SHORT_FLAG_CENTER 'C'
#define OPTION_RADIUS "radius", required_argument, NULL, 'r'
#define SHORT_FLAG_RADIUS 'r'
#define OPTION_TRIM "trim", no_argument, NULL, 'T'
#define SHORT_FLAG_TRIM 'T'
#define OPTION_LEFT_UP "left_up", required_argument, NULL, 'L'
#define SHORT_FLAG_LEFT_UP 'L'
#define OPTION_RIGHT_DOWN "right_down", required_argument, NULL, 'R'
#define SHORT_FLAG_RIGHT_DOWN 'R'
#define OPTION_HELP "help",no_argument, NULL, 'h'
#define SHORT_FLAG_HELP 'h'
#define OPTION_CONTRAST "contrast", no_argument, NULL, 'm'
#define SHORT_FLAG_CONTRAST 'm'
#define OPTION_ALPHA "alpha", required_argument, NULL, 'M'
#define SHORT_FLAG_ALPHA 'M'
#define OPTION_BETA "beta", required_argument, NULL, 'y'
#define SHORT_FLAG_BETA 'y'
#define VOID_OPTION 0, 0, 0, 0

#define FINISH_OPTS -1

typedef struct
{
    int width;
    int height;
    png_byte bit_depth;
    png_byte color_type;
    png_byte channels;
    png_infop info_ptr;
    png_structp png_ptr;
    png_bytep *row_pointers;    
} Png;

typedef struct {
    int start_x, start_y;
    int end_x, end_y;
    int border_color[MAX_COLOR_COMPONENT];
    int fill_color[MAX_COLOR_COMPONENT];
    int thickness;
} Liner;

typedef struct {
	int start_x, start_y;
	int radius;
} Inverser;

typedef struct{
	int start_x,start_y;
	int end_x,end_y;
}Trim;

typedef struct {
    int start_x, start_y, end_x, end_y, mid_x, mid_y;
    int radius;
    float alpha;
    int beta;
    int border_color[MAX_COLOR_COMPONENT];
    int fill_color[MAX_COLOR_COMPONENT];
    int thickness;
    int isFill;
} Data;

typedef struct{
	int beta;
	float alpha;
}Contrast;



#endif
