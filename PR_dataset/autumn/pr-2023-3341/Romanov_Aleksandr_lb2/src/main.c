#include <stdio.h>
#define N 100
#include <stdlib.h>
#define flags "%d\n"
#define spc ' '
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_before_even_and_after_odd.h"
#include "sum_between_even_odd.h"

int output(int value, int count, int *arr) {  
    switch(value){

        case 0:
        	printf(flags,index_first_even(arr, count));
        	break;
        case 1:
        	printf(flags,index_last_odd(arr, count));
        	break;
        case 2:
        	printf(flags,sum_between_even_odd(arr, count));
        	break;
        case 3:
        	printf(flags,sum_before_even_and_after_odd(arr, count));
        	break;
        default:
        	puts("Данные некорректны");
        	break;
    }
}

int input_value(){
    int value;
    scanf("%d", &value);
    return(value);
}

int input_arr(int arr[]){
    int count=0;
    char space = ' ';
    while (count<N && space == spc){
        scanf("%d%c", &arr[count],&space);
        count++;
    }
    return count;
}

int main(){
    int value = input_value();
    int arr[N];
    int count = input_arr(arr);
    output(value,count,arr);
}

