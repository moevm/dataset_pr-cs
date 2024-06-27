#include <stdio.h>
#include <stdlib.h>
#include "index_last_odd.h"
#include "index_first_even.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"

int array[101];
int sizeOfArray = 0, func;

int main(){
    scanf("%d", & func);
    while(getchar() != '\n'){
        scanf("%d", & array[sizeOfArray]);
        ++sizeOfArray;
    }
    switch(func){
        case 0:
            printf("%d", index_first_even(array, sizeOfArray));
            break;
        case 1:
            printf("%d", index_last_odd(array, sizeOfArray));
            break;
        case 2:
            printf("%d", sum_between_even_odd(array, sizeOfArray));
            break;
        case 3:
            printf("%d", sum_before_even_and_after_odd(array, sizeOfArray));
            break;
        default:
            puts("Данные некорректны");
    }
}
