#pragma once
#include <cstring>
#include "image.hpp"

void exchange(Image *, int, int, int, int, int);

void copyrect(uint8_t **, uint8_t **, int, int, int, int, int, int);

uint8_t **newtable(int, int);
