#include <stdio.h>
#include "index_last_negative.h"

int index_last_negative(int arr[],int arr_len){
        int j,temp = -2;
        for(j=0;j<arr_len;j++){
                if(arr[j] < 0)
                        temp = j;}
        return temp;
}
