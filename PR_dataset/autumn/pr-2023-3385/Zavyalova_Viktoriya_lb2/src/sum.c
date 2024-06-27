#include "sum.h"
#include "min.h"

int sum(int arr[],int len){
    int b = 0,z = min(arr,len);
    for(int i = 0;arr[i] != z;i++){
        b = b + arr[i];
    }
    return b;
}

 