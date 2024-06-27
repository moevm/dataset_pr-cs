#include "index_last_negative.h"
int index_last_negative(int array[], int len){
    for (int i=len-1; i>=0; i--){
        if (array[i]<0){
            return i;
        }
    }
    return -1;
}