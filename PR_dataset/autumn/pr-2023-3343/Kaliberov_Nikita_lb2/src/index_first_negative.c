#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"

int index_first_negative(int b[], int s){
    int i_fn;
    for(int i=0;i<s;i++){
        if(b[i]<0){
            i_fn = i;
            break;
        }
    }
    return i_fn;
}
