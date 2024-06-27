#include <stdio.h>
#include <stdlib.h>
#include "input.h"


int input(int array[],int* array_size){
    int operation_number;
    char space = ' ';
    scanf("%d", &operation_number);
    while (*array_size < 100 && space == ' ') {
        scanf("%d%c", &array[*array_size], &space);
        *array_size = *array_size + 1;
        }
    return operation_number;
}
