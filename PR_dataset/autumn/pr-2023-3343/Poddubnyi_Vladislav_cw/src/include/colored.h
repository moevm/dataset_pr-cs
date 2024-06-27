//
// Created by rect on 17.11.2023.
//

#ifndef CW_COLORED_H
#define CW_COLORED_H

#include <string.h>
#include <wchar.h>
#include <stdlib.h>

#include "structs.h"

#define RED     L"\x1b[31m"
#define GREEN   L"\x1b[32m"
#define YELLOW  L"\x1b[33m"
#define BLUE    L"\x1b[34m"
#define DEFAULT L"\x1b[0m"

Text getColored(Text text);
#endif //CW_COLORED_H
