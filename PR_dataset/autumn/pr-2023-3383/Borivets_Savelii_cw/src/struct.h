#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>

struct Sentence {
    wchar_t *sen;
    size_t ln_sen;
};
struct Text {
    wchar_t **txt;
    size_t cnt_sen;
};