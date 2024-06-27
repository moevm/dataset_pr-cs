#include <stdlib.h>

int abs_max(int arr[], int count)
{
    int maxim_abs = -1;
    int maxim_ind = 0;
    for(int i = 0; i < count; ++i){
        if(maxim_abs < abs(arr[i])){
            maxim_abs = abs(arr[i]);
            maxim_ind = i;
        }
    }
    return arr[maxim_ind];
}
