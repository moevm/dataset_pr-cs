#include "abs_max.h"
#include "abs_min.h"
int diff(int arr_len, int arr[]){
        return abs_max(arr_len, arr) - abs_min(arr_len, arr);
}
