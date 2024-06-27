#pragma once

#include <locale.h>
#include <wchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <wctype.h>
#include <time.h>
#include <stdint.h>
#include <string.h>

#define MUL_MEM 2
#define u8 uint8_t
#define u16 uint16_t

typedef struct{
    wchar_t* data;
    size_t size;
} sentence_t;

typedef struct{
    sentence_t **data;
    size_t size;
} text_t;

typedef struct{
    char* date;
    time_t time;
}date_t;

char *strptime(const char *s, const char *format, struct tm *tm);
#include "printF_text.h"


