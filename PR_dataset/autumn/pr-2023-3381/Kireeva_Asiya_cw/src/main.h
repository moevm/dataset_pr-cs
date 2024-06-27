#ifndef MAIN
#define MAIN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <math.h>
#include "get_text.h"
#include "zero_func.h"
#include "first_func.h"
#include "second_func.h"
#include "third_func.h"
#include "fourth_func.h"
#include "fifth_func.h"
#include "ninth_func.h"
#include "free_space.h"
#define ADD_SIZE 8

struct Sentence {
    wchar_t *sentence;
    int number_of_letters;
    int first_word_summ;
};

struct Text {
    struct Sentence **text;
    int number_of_sentences;
};
#endif