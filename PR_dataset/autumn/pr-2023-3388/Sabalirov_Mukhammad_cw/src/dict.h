#pragma once

#include <stdlib.h>
#include "structs.h"
#include "ioroutine.h"

#define DICT_ERROR L"Error: Key find fail\n"
size_t find_value(wchar_t, struct Dict*, size_t);