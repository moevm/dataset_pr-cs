#include <stdio.h>

void input(int *arr, int *arr_size){
    while (getchar() != '\n') {
        scanf("%d", &arr[(*arr_size)++]);
    }
}