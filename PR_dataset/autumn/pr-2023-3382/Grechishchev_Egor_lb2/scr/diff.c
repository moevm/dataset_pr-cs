#include <stdio.h>
#include <stdlib.h>
#include "abs_max.h"
#include "abs_min.h"

int diff(int arr[] , int size){
    int dif = abs_max(arr, size) - abs_min(arr, size);
    return dif;
}