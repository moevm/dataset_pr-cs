#ifndef REPLACE_SYMBOL_H 
#define REPLACE_SYMBOL_H

#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

void replaceSymbol(Sentence* sentence, wchar_t symbol, wchar_t* replace_symbol);

#endif