#include <stdio.h>
#include "index_first_negative.h"

int index_first_negative(int arr[],int arr_len){
        int j,flag = 0;
        for(j=0;j<arr_len;j++)
                if(arr[j] < 0){
                        return j;
                        flag = 1;
                        break;}
        if(flag==0)
                return -2;
}
