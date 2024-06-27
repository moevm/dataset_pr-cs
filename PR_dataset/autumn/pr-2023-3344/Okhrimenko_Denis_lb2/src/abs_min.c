#include <stdlib.h>

int abs_min(int arr[], int count)
{
    int minim_abs = abs(arr[0]);
    int minim_ind = 0;
    for(int i = 1; i < count; ++i){
        if(minim_abs > abs(arr[i])){
            minim_abs = abs(arr[i]);
            minim_ind = i;
        }
    }
    return arr[minim_ind];
}
