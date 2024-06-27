#pragma once
#include <wchar.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>

#include "structures.h"
#include "text_base_funct.h"


Text *input_text();
Sentence *read_sentence();
void print_text(Text *text);
