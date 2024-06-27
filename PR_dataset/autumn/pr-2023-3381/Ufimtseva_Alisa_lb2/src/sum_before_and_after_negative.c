#include "sum_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
#define N 100

int arr[N];

int sum_before_and_after_negative (){
    int first=index_first_negative(arr);
    int last=index_last_negative(arr);
    int sum=0;
    if (first==-1){
        return -1;
    }
    else{
        for (int i=0; i<first; i++){
            sum+=arr[i];
        }
        for (int i=last; i<N; i++){
            sum+=abs(arr[i]);
        }
        return sum;
    }
}