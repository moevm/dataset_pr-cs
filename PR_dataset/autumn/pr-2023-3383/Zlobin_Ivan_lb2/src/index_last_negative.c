#include "index_last_negative.h"

int index_last_negative(int arr[]){
        for(int i=99;i>=0;--i){
                if(arr[i]<0)
                        return i;
        }
}

