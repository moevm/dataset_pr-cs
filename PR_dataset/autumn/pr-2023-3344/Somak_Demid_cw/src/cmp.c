#include "cmp.h"


int cmp(const void *a, const void *b)
{
    Sentence *first = *(Sentence **)a;
    Sentence *second = *(Sentence **)b;

    unsigned lenfirst = (first->countwords >= 3) ? wcslen(first->arrofwords[2]) : 0;
    unsigned lensecond = (second->countwords >= 3) ? wcslen(second->arrofwords[2]) : 0;

    return lenfirst - lensecond;
}