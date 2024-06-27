#include <stdio.h>
#include "input.h"

#define N 100


void input(int *key, int arr[N],int *arr_elements_count){
    char space=' ';
    scanf("%d", &*key);
    while (*arr_elements_count<N && space == ' '){
        scanf("%d%c", &arr[*arr_elements_count], &space);
        *arr_elements_count=*arr_elements_count+1;
    }
}