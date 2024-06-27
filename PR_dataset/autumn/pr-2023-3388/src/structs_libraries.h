#pragma once

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wctype.h>
#include <wchar.h>

#define START_SIZE 10 
#define COURSE_WORK_INFO L"Course work for option 5.14, created by Shubin Pavel.\n"
#define MEMORY_ERROR L"Ошибка перераспределения памяти.\n"

struct Text {
    struct Sentence **sentences;
    int amount_of_sentences;
};

struct Sentence {
    wchar_t *sentence;
    struct Word **words;
    int amount_of_words;
};

struct Word {
    wchar_t *word;
    int len;
};