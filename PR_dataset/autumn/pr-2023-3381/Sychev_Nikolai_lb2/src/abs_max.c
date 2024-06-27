#include <stdio.h>
#include <stdlib.h>

int abs_max(int arr[], int len_arr){
    int ans = 0, maxim = 0;
    for(int i = 0; i < len_arr; i++){
            if (abs(arr[i]) > maxim){
                maxim = abs(arr[i]);
                ans = arr[i];
            }
        }       
    return ans; 
}