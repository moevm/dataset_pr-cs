#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>
#define MEM_STEP 100
#define GREEN "\033[32m"
#define NONE "\033[0m"
#define SEPARATORS L" \t\n,."
#define ALPHABET L"\"'+/\\~[]&`|{}=_<>-();:#$^%@*!??1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNMёйцукенгшщзхъфывапролджэячсмитьбюЁЙЦУКЕНГШЩЗХЪФЫВАПРОЛДЖЭЯЧСМИТЬБЮ"
struct Sentence {
    wchar_t *str;
    int size;
    int len;
    int countwords;
};


struct Text {
    struct Sentence **array;
    int n;
    int size;
};
