#include "diff.h"
#include "abs_max.h"
#include "abs_min.h"

int diff(int array_num[], int length){
    return abs_max(array_num, length) - abs_min(array_num, length);
}