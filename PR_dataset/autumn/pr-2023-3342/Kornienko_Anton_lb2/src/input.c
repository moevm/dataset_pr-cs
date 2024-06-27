#include <stdio.h>
#include <stdlib.h>
#include "input.h"
#define N 100


int input(int array[],int* ptr_len){
    int command_number;
    char space = ' ';
    scanf("%d", &command_number);
    while (*ptr_len < N && space == ' ') {
        scanf("%d%c", &array[*ptr_len], &space);
        *ptr_len = *ptr_len + 1;
        }
    return command_number;
}
