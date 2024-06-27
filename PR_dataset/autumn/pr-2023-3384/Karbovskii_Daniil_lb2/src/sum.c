#include <stdio.h>
#include "sum.h"
#include "min.h"
int sum(int arr[], int n){
    int sum = 0;
    for(int i=0;arr[i]!=min(arr, n) && i<n;i++){
        sum += arr[i];
    }
    return sum;
}
