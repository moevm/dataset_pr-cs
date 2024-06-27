#include <stdio.h>
#include <stdlib.h>
#include "abs_min.h"
#include "abs_max.h"

int diff(int arr[], int len){
    return abs_max(arr, len) - abs_min(arr, len);
}

