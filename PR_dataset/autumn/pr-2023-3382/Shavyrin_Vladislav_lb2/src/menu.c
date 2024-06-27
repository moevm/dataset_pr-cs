#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"

int main(){
    char sym;
    int option, arr[100], size_arr = 0;
    scanf("%d%c", &option, &sym); // Выбор варианта
    for(int i = 0; i < 100; i++){
        scanf("%d%c", &arr[i], &sym);
        size_arr++;
        if (sym == '\n'){ // Проверка на конец ввода
            break;
        }
        
    }
    switch(option){
        case 0:
            printf("%d\n", index_first_even(arr, size_arr));
            break;
        case 1:
            printf("%d\n", index_last_odd(arr, size_arr));
            break;
        case 2:
            printf("%d\n", sum_between_even_odd(arr, size_arr));
            break;
        case 3:
            printf("%d\n", sum_before_even_and_after_odd(arr, size_arr));
            break;
        default:
            printf("Данные некорректны\n");
    }
    return 0;
}
