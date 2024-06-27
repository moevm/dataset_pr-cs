#ifndef PARSING_H
#define PARSING_H

#include "main.h"

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int is_number(const char* str);
void raise_error(Configs* config, char* message, int return_code);
void init_configs(Configs* config);
void free_memory(Configs* config);
void parsing_coordinates(const char* flag, Configs* config, const char* optarg);
void parsing_angle(Configs* config, const char* optarg);
void parsing_number(const char* flag, Configs* config, const char* optarg);
void parsing_color(const char* flag, Configs* config, const char* optarg);
void parsing_component_name(Configs* config, const char* optarg);
void parsing_component_value(Configs* config, const char* optarg);

#endif
