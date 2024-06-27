#include "index_first_negative.h"

int index_first_negative(int arr[]){
        for(int i=0;i<100;++i){
                if(arr[i]<0)
                        return i;
        }
}

