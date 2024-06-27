#include <stdio.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_before_and_after.h"
#include "sum_between.h"

int main(){
    int a;
    int size=0;
    int array[100];
    scanf("%d", &a); 
    while (scanf("%d", &array[size])==1){ 
        size++;
        if (getchar()=='\n'){ 
            break;
        }
    }

   

    switch(a){
        case 0:
            printf("%d\n", index_first_zero(array, size));
            break;
        case 1:
            printf("%d\n", index_last_zero(array, size));
            break;
        case 2:
            printf("%d\n", sum_between(array, size));
            break;
        case 3:
            printf("%d\n", sum_before_and_after(array, size));
            break;
        default:
            printf("Данные некорректны \n");
            break;
    }
    return 0;
} 
