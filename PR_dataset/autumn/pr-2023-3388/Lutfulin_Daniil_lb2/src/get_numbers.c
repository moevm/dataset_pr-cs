#include <stdlib.h>
#include <stdio.h>

#ifndef MAX_SIZE
#define MAX_SIZE 100
#endif

void get_numbers(int *real_len, int *case_num, int **arr){
    int arr_len=0;
    int first_number;
    scanf("%d", case_num);
    *arr = malloc(MAX_SIZE * sizeof(int));
    do {
      scanf("%d", &(*arr)[arr_len]);
      arr_len++;
    } while (getchar() != '\n');
    *real_len = arr_len;
}