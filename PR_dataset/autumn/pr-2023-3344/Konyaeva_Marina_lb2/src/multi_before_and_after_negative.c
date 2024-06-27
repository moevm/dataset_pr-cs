#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_before_and_after_negative(int arr[],int n){
    int mul = 1;
    for (int i = 0; i < index_first_negative(arr, n); i++) {
        mul = mul * arr[i];
    }
    for (int i = index_last_negative(arr,n); i < n; i++){
        mul = mul * arr[i];
    }
    return mul;
}
