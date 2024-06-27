#pragma once
#include "../include/rgb.h"
#include "../include/draw_line.h"

void find_and_recolor_biggest_rect(RGB *image, int w, int h, const RGB &oldColor, const RGB &newColor);
