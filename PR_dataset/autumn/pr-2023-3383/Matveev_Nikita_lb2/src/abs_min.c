#include <stdio.h>
#include <stdlib.h>
#include "abs_min.h"
int abs_min(int c, int* arr){
    int mn = abs(arr[0]);
    int mnn = arr[0];
    for(int i=0; i<c; i++){
        if(abs(arr[i]) < mn){
            mn = abs(arr[i]);
            mnn = arr[i];
        }
    }
 
    return mnn;
}
