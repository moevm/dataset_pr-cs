#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
int index_first_negative(int num_list[], int list_len){
    for(int i = 0; i <list_len; i++){
        if (num_list[i]<0){
            return i;}}}
