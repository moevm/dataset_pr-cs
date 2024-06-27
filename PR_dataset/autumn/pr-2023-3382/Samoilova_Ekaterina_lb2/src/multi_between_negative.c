#include <stdio.h>
#include "index_first_negative"
#include "index_last_negative"
int multi_between_negative(int arr[], int N){
        int ifn=index_first_negative(arr,N);
        int iln=index_last_negative(arr, N);
        int res=1;
        for (ifn; ifn<iln ;ifn++){
            res=res*arr[ifn];};
        return res;
    return 0;
    };