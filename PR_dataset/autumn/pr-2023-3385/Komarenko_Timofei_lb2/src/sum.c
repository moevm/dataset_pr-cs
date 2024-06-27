#include "sum.h"
#include "abs_max.h"

int sum(int array[], int len){
    int sum_after_max = 0;
    int ind_max = 0;
    int max = abs_max(array, len);
    for (int i = 0; i < len; i++){
        if (array[i] == max){
        	ind_max = i;
        	break;
        }
    }
    for(int i = ind_max; i < len; i++){
    	sum_after_max += array[i];
    }
    return sum_after_max;
}
