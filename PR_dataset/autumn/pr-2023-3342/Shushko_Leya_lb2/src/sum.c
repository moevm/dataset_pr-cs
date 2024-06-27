#include "sum.h"
int sum(int arr[],int size){
    int sum =0;
    int minimum = min(arr,size);
    for (int i = 0;i<size;i++){
        if (arr[i]==minimum){
        break;
        }
        sum = sum + arr[i];
    }
    return sum;
}
