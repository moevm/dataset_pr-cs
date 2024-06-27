#include <stdio.h>
#include "max.h"
#include "min.h"

int diff(int array[100], int len){
    return max(array, len) - min(array, len);
}
