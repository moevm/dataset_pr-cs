#include "diff.h"
#include "abs_max.h"
#include "abs_min.h"
int diff(int arr[], int len) {
    int max = abs_max(arr, len);
    int min = abs_min(arr, len);
    int rez = max - min;
    return rez;
}