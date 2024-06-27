#include <stdio.h>
#include <stdlib.h>

int index_last_odd(int arr[], int len){
    
    for(int i=len-1; i>-1; i--){
        if(abs(arr[i] % 2) == 1){
            return(i);
            break;
        }
    }
   
}
