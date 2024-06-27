#pragma once

#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>
#include <stdio.h>
#include <ctype.h>

//Структуры
struct Sentence {
    wchar_t *sentence;
    wchar_t **words_arr;
    unsigned word_counter;
    wchar_t *seps_arr;
    unsigned sep_counter;
    unsigned sent_len;
};

struct Text {
    struct Sentence **sentences_arr;
    unsigned sent_counter;
};