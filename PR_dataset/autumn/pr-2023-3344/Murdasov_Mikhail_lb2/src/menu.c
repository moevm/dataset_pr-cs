#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"


int main(){
    int a;
    int i;
    int arr[100];
    int ind_count;

    scanf("%d", &a);

    if(a != 0 && a != 1 && a != 2 && a != 3){
        puts("Данные некорректны\n");
        return 0;
    }
    
    for(i = 0; i<100 && getchar() != '\n'; i++){
        scanf("%d", &arr[i]);
        ind_count = i+1;
    }

    switch(a){
        case 0:
            printf("%d\n", index_first_even(arr, ind_count));
            break;
        case 1:
            printf("%d\n", index_last_odd(arr, ind_count));
            break;
        case 2:
            printf("%d\n", sum_between_even_odd(arr, ind_count));
            break;
        case 3:
            printf("%d\n", sum_before_even_and_after_odd(arr, ind_count));
            break;
        
        default:
            puts("Данные некорректны\n");
            break;
    }

    return 0;
}