#include <stdio.h>
#include "diff.h"
#include "abs_max.h"
#include "abs_min.h"
int diff(int c, int* arr){
    int d =0;
    d = abs_max(c, arr) - abs_min(c, arr);
    return d;
}
