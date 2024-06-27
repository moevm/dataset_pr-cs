#include <stdio.h>
#include "input.h"

#define N 100


void input(int *func_id, int arr[N],int  *arr_elements_quantity){
    char space=' ';
    scanf("%d", &*func_id);
    while (*arr_elements_quantity<N && space == ' '){
        scanf("%d%c", &arr[*arr_elements_quantity], &space);
        *arr_elements_quantity=*arr_elements_quantity+1;
    }
}