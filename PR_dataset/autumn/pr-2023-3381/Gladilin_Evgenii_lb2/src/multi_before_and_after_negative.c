#include <stdio.h>
#include "multi_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_before_and_after_negative(int arr[],int arr_len){
        int first = index_first_negative(arr,arr_len),last = index_last_negative(arr,arr_len),pr=1,counter;
        if(last == -2){
                printf("Данные некорректны\n");
        }else{
                for(counter = 0;counter<first;counter++){
                        pr = pr*arr[counter];}
                for(last;last<arr_len;last++){
                        pr = pr*arr[last];}
        printf("%d\n",pr);
        }
}

