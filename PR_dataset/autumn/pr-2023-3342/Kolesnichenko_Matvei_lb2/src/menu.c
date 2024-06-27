#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_before_and_after.h"
#include "sum_between.h"
#include "input.h"
#include "switcher.h"

#define MAX_SIZE 101
#define OUT_PATTERN "%d\n"

int main(){
    int num;
    int arr_size = 0;
    int arr[MAX_SIZE];

    scanf("%d", &num);
    input(arr, &arr_size);

    switcher(num, arr, arr_size);
    
    return 0;
}