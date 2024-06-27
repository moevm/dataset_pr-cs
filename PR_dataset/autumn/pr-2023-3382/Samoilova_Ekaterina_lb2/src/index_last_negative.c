#include <stdio.h>
int index_last_negative(int arr[], int N){
        int index;
        for (index=N-1; index>0; index--)
            if (arr[index]<0){
            return index;
            break;
            };
        return 0;
        };