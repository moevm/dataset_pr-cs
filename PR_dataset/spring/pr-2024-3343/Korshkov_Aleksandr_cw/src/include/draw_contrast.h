#ifndef DRAW_CONTRAST_H
#define DRAW_CONTRAST_H

#include "../include/add_operations.h"
#include "../include/png_objects.h"

void set_alpha(char *alpha, info_contrast *contrast);
void set_beta(char *beta, info_contrast *contrast);
void set_contrast(info_contrast *contrast, Png* png);
#endif
