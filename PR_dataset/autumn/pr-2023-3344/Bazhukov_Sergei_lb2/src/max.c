#include "max.h"

int max(int *array,int arr_len){
    int maxon=array[0];
    for (int i=0; i<arr_len; i++){
        if(array[i]>maxon){
            maxon=array[i];
        }
    }
    return maxon;
}