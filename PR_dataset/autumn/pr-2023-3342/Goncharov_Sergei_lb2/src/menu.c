#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"
#include "input.h"
#include "output.h"
#define N 100

int main(){
    int array[N];
    int length = 0;
    int* array_size = &length;
    int operation_number = input(array, array_size);
    output(operation_number, array, length);

    return 0;
}
