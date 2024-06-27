#pragma once
#include "library.h"


void read_png_file(char *file_name, struct Png *img);
void write_png_file(char *file_name, struct Png *img);
void print_png_info(struct Png *img);
void print_help();
void free_image_data(struct Png *img);
void create_default(struct Configs* conf);
void free_conf(struct Configs* conf);
void create_defaut_for_flags(struct Flags* flag);
