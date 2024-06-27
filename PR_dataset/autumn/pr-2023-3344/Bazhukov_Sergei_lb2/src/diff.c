#include "diff.h"
#include "max.h"
#include "min.h"

int diff(int *array,int arr_len){
    int difference = max(array,arr_len)-min(array,arr_len);
    return difference;
}