#include "min.h"

int min(int *array,int arr_len){
    int minon=array[0];
    for (int i=0; i<arr_len; i++){
        if(array[i]<minon){
            minon=array[i];
        }
    }
    return minon;
}