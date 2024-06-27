#include "diff.h"
#include "abs_min.h"
#include "abs_max.h"

int diff(int array[], int len){
    int max = abs_max(array, len);
    int min = abs_min(array, len);
    return max-min;
}
