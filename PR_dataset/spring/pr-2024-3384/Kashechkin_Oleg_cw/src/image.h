#pragma once

#include "main.h"

image *open_image(char *path);
int save_image(image *img, char *path);
void free_image(image *img);