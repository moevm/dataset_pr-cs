#pragma once

#include "bmp_structs.h"

void process_center_input(char* optarg, int* x_coord, int* y_coord);

int process_integer_input(char* optarg, int* radius);

void process_color_input(char* optarg, Rgb* color, int flag);

void process_component_name(char* optarg, char* component_name);

void process_component_value(char* optarg, int* component_value);

int process_split_coords_input(char* optarg, int* radius);

int process_file_name(char* optarg, char*output_file_name);

void check_for_inputfile(int argc, char** argv, char* filename, int optind);