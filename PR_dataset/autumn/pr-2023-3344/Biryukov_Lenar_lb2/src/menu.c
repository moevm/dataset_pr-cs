#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"
#define N 100

int main(){
    int arr[N] = {0}, task, i = 0;
    char symbol;
    scanf("%d", &task);
    while(symbol != '\n'){
    scanf("%d%c", &arr[i], &symbol);
    ++i;
    }
    switch(task){
        case 0:
            printf("%d\n", index_first_even(arr));
            break;
        case 1:
            printf("%d\n", index_last_odd(arr));
            break;
        case 2:
            printf("%d\n", sum_between_even_odd(arr));
            break;
        case 3:
            printf("%d\n", sum_before_even_and_after_odd(arr));
            break;
        default:
            puts("Данные некорректны\n"); 
    }
    return 0;
}
