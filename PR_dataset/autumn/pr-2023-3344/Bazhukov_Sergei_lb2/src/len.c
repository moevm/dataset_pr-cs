#include "len.h"

int len(int *array){
    int arr_len=0;
    do{
       scanf("%d",&array[arr_len]);
       arr_len++;
    } while (getchar()!='\n');
    return arr_len;
}