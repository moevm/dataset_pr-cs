#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"
#define MAX_SIZE 100

int main(){
    int operation, result;
    result = 0;
    scanf("%d", &operation);
    int size = 0;

    int arr[MAX_SIZE];
    char end_line;
    do{
       scanf("%d%c", &arr[size], &end_line);
       size++;
    }while(end_line!='\n' && size<MAX_SIZE);
    switch(operation){
        case 0:
            result = index_first_even(arr, size);
            printf("%d\n", result);
            break;
        case 1:
            result =index_last_odd(arr, size);
            printf("%d\n", result);
            break;
        case 2:
            result =sum_between_even_odd(arr, size);
            printf("%d\n", result);
            break;
        case 3:
            result =sum_before_even_and_after_odd(arr, size);
            printf("%d\n", result);
            break;
        default:
            puts("Данные некорректны");
            break;
    }
    return 0;
}

