#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdlib.h>
#include "const.h"
#include "image.h"
#include "parser.h"

void panic(char* msg);

#define CHECK_FLAG(flag_value) ((config->error_flag & flag_value) != 0)
TaskConfig* read_args(int argc, char** argv);

Image* read_png(string* filename);

void save_png(Image* img, string* filename);

void print_info(Image* img);

Image* process_image(TaskConfig* config, Image* img);

#endif /* IO_H */
