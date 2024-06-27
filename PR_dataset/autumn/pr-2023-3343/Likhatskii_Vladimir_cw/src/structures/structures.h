#include <wchar.h>
#include <stdlib.h>

#pragma once
#include "../config/config.h"
#pragma once
#include "../helpers/helpers.h"

typedef struct {
    wchar_t * text; 
} Sentence;

typedef struct {
    int length; 
    Sentence * sentences;
} Text;

Text *Text_from_string(wchar_t *); 
void Text_push(Text *text, wchar_t * sentence_text);