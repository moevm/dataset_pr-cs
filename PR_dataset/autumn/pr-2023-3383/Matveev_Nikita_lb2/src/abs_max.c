#include <stdio.h>
#include <stdlib.h>
#include "abs_max.h"
int abs_max(int c, int* arr){
    int mx = abs(arr[0]);
    int mxx = arr[0];
    for(int i=0; i<c; i++){
        if(abs(arr[i]) > mx){
            mx = abs(arr[i]);
            mxx = arr[i];
        }
    }
 
    return mxx;
}
