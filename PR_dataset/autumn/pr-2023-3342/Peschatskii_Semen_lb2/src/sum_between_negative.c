#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
int sum_between_negative(int num_list[], int list_len){int sum = 0;
    for(int i = index_first_negative(num_list,list_len); i<= index_last_negative(num_list,list_len); i++){
        sum = sum + abs(num_list[i]);
    }
    return sum;}
