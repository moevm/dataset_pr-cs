#include <stdio.h>
#include "multi_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_between_negative(int arr[],int arr_len){
        int first = index_first_negative(arr,arr_len),last = index_last_negative(arr,arr_len),pr=1;
        if(last == -2){
                printf("Данные некорректны\n");
        }else{
                for(first;first<last;first++){
                        pr = pr*arr[first];}
        printf("%d\n",pr);
        }
}
