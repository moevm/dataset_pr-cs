#include <stdlib.h>
int abs_max(int arr[], int arrsize, int r){
    int max = 0; 
    int maxindex, i;
    for (i = 0; i < arrsize; i++){
        if (abs(arr[i]) > abs(max)){
            max = arr[i];
            maxindex = i;
        }
    }
    if (r){
        return max;
    }
    else{
        return maxindex;
    }
}