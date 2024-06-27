#pragma once
#include "structs.h"
#include "leave.h"

#define SENT_END L'\0'
#define SPECIAL_SYMBOLS L"№*$#@.,;"
#define REPLACE L">special symbol<" 

Sentence *replace_special_symbols(Sentence*);
void replace_special_in_text(Text*);

