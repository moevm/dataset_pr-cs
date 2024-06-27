#include <stdio.h>
#include <stdlib.h>
#include "abs_max.h"
#include "abs_min.h"
#include "diff.h"
#include "sum.h"
#include "input.h"
#include "output.h"

#define N 100


int main() {
    int key = 0;
    int arr[N];
    int i = 0;

    input(&key, arr, &arr_elements_count);
    output(&key, arr, &arr_elements_count);

    return 0;
}
