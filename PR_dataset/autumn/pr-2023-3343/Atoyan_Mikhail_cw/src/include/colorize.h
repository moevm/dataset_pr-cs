#ifndef COLORIZE_H
#define COLORIZE_H

#include <stdlib.h>
#include <stdio.h>
#include <wctype.h>


#include "structures.h"

#define GREEN   L"\x1b[32m"
#define DEFAULT L"\x1b[0m"

void print_colorized(Text text);

#endif //COLORIZE_H