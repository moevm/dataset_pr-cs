#include "compare.h"

int compare(const void* a, const void* b)
{
    date_t* x = *(date_t**)a;
    date_t* y = *(date_t**)b;
    if(x->time > y->time) return 1;
    if(x->time < y->time) return -1;
    return 0;
}
