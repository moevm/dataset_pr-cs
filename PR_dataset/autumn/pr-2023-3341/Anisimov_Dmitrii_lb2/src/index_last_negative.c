#include "index_last_negative.h"

int index_last_negative(int *arr, int counter){
    int index_l_n;
    int i;
    for (i=0;i<counter;i++){
        if (arr[i]<0){
        index_l_n=i;
        }
    }
    return index_l_n;
}