
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <regex.h>
#include "structures.h"

int *parse_coords(char *coords);
int *parse_color(char *color);
void check_one_coords(char *coords);
void check_size(char *radius);
void check_thickness(char *thickness);
void check_color(char *color);
void check_component_name(char *color);
void check_angle(char *angle);
void check_flo(char *thickness);
