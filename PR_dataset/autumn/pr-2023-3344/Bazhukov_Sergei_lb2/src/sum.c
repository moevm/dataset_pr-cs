#include "sum.h"
#include "min.h"

int sum(int *array,int arr_len){
    int sum=0;
    int minon = min(array,arr_len);
    for(int i=0;array[i]>minon;i++){
        sum=sum+array[i];
    }
    return sum;
}