#include <stdio.h>
#include <stdlib.h>
#include "sum_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
int sum_before_and_after_negative(int num_list[], int list_len){int totsum =0;
	int  first_index = index_first_negative(num_list, list_len);
	int last_index = index_last_negative(num_list, list_len);
    for(int i = 0; i <= first_index; i++){totsum = totsum + abs(num_list[i]);}
    for(int i = list_len; i > last_index; i--){totsum = totsum + abs(num_list[i]);}
    return totsum;
}
