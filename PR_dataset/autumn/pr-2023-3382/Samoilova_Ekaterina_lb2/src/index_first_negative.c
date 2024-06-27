#include <stdio.h>
int index_first_negative(int arr[], int N){
        int index;
        for (index=0; index<N; index++)
            if (arr[index]<0){
            return index;
            break;
            };
        return 0;
        };