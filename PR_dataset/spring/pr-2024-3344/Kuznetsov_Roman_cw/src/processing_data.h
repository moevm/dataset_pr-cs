#ifndef PROCESSING_DATA_H
#define PROCESSING_DATA_H
#include "bmp_reader.h"
#include "print_func.h"

typedef struct Arguments {
  char* out_name;
  char* in_name;
  int out_flag;
  int in_flag;
  int flag_info;
  int flag_help;
  
  int flag_num_y;
  int num_y;
  int flag_num_x;
  int num_x;
  
  int flag_collage;
  int flag_pentagram;
  int flag_rect;
  int flag_mirror;
  int flag_rhombus;
  
  
  int flag_axis;
  int axis;
  int flag_left_up;
  coord left_up;
  int flag_right_down;
  coord right_down;
  int flag_center;
  int center[2];
  int flag_radius;
  int radius;
  int flag_thickness;
  int thickness;
  int flag_color;
  rgb color;
  int flag_fill_color;
  rgb fill_color;
  int fill;
  
} Arguments;

void swap(int* a, int* b);
int more_zero(int arg);
void less_then(int arg);
void more_then_zero(int arg);
void check_axis(char* optarg);
void another_arguments(char* arg, char* name);
void check_bmp(char* name);
void check_coord(char* coords);
void check_digit(char * distance);
int* parse_color(char* color);
int* parse_color(char* color);
Arguments get_arguments(int argc, char *argv[]);

#endif
