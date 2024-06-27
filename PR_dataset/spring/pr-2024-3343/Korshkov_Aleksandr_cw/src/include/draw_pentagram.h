#ifndef DRAW_PENTAGRAM_H
#define DRAW_PENTAGRAM_H

#include "../include/draw_pentagram.h"
#include "../include/draw_line.h"

void draw_pentagram(int x0, int y0, int radius, int thickness, RGB color, Png *png);
int check_pentagram(info_pentagram *pentagram);
void set_radius(char *radius, info_pentagram *pentagram);
void set_center(char *center, info_pentagram *pentagram);
void set_color_pentagram(char *color, info_pentagram *pentagram);
void set_thickness_pentagram(char *thickness, info_pentagram *pentagram);

#endif