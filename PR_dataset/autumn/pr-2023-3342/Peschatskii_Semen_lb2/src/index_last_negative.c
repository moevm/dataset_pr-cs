#include <stdio.h>
#include <stdlib.h>
#include "index_last_negative.h"
int index_last_negative(int num_list[], int list_len){
    for(int j = list_len-1; j>=0;j--){
        if (num_list[j]<0){
            return j;}}}
