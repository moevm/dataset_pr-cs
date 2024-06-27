#include <stdio.h>
#include <stdlib.h>
#include "index_last_negative.h" 

int index_last_negative(int b[], int s){
    int i_ln;
    for(int i=s-1;i>=0;i--){
        if(b[i]<0){
            i_ln = i;
            break;
        }
    }
    return i_ln;
}
