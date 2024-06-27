#include <stdio.h>
#include "sum.h"
#include "abs_max.h"
int sum(int c, int* arr){
    int maximus=0;
    maximus=abs_max(c, arr);
    int summar = 0;
    int index = 0;
 
    for(int i=0; i<c; i++){
        if(arr[i]==maximus){
            index = i;
            break;
        }
    }
    for(int i=index; i<c; i++){
        summar += arr[i];
    }
    return summar;
}
