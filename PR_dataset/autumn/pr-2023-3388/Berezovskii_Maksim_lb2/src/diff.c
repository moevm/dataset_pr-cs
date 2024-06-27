#include <stdlib.h>
#include "diff.h"
#include "abs_min.h"
#include "abs_max.h"

int diff (int array[], int index_max, int index_min){
    return array[index_max] - array[index_min];
}