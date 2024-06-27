#ifndef main_lib_h
#define main_lib_h

#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <locale.h>

struct Sentence{
    wchar_t *str;
    unsigned long int len;
    float midlen;
    int cnt;
};
struct Text{
    struct Sentence **sentences;
    int num_of_sent;
};

#endif
