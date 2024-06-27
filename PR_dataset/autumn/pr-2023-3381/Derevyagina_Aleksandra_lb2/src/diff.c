#include "diff.h"
#include "max.h"
#include "min.h"

int diff(int array[], int index){
    return max(array, index) - min(array, index);
}

