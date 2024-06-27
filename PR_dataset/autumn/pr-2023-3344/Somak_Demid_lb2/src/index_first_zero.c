#include "index_first_zero.h"

int first_zero(int M[],int end){
    int indfrs;
    for(int i = 0;i < end;i++){
        if(M[i] == 0){
            indfrs = i;
            break;
        } 
    }    
    return indfrs;
} 
