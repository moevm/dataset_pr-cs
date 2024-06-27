#ifndef param
#define param
#include <getopt.h>
#include <structs.h>
#include <stdlib.h>
#include <string.h>
#include <png_edit.h>
void init_params(params_t* params);
void raise_arg_error();
void parse_coords(char* arg, int* x, int* y);
void parse_rgb(char* arg, rgb_t* rgb);
void parse_params(params_t* optparams, int argc, char** argv);
#endif