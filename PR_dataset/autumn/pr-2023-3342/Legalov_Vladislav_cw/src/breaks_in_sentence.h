#pragma once
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>

#include "structures.h"
#include "wchar_checks.h"




void insert_breaks(Sentence* sentence, BreaksData* breaks);
BreaksData* create_breaks_data(int *array, int size, int size_breaks);
void free_breaks_data(BreaksData* breaks);
