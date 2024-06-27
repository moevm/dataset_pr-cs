#include <stdio.h>
#include "index_first_negative"
#include "index_last_negative"
int multi_before_and_after_negative(int arr[], int N){
        int index=0;
        int ifn=index_first_negative(arr,N);
        int iln=index_last_negative(arr, N);
        int res_before=1;
        int res_after=1;
        for (index; index<ifn;index++){
            res_before = res_before *arr[index];};
        for (iln; iln<N; iln++){
            res_after = res_after *arr[iln];
        }
        return  res_before * res_after;
        
    return 0;
    };