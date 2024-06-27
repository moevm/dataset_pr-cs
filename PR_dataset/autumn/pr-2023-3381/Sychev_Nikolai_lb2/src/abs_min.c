#include <stdio.h>
#include <stdlib.h>

int abs_min(int arr[], int len_arr){
    int ans = arr[0];
    int minim = abs(arr[0]);
        for(int i = 1; i<len_arr; i++){
            if (abs(arr[i]) < minim){
                minim = abs(arr[i]);
                ans = arr[i];
            }
        }
    return ans;
}
