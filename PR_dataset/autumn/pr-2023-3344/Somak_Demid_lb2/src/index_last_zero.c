#include "index_last_zero.h"

int last_zero(int M[],int end){
    int indlast;
    for(int i = 0;i < end;i++){
        if(M[i] == 0){
            indlast = i;
        }
    }
    return indlast;
}

