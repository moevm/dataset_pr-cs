#include <stdio.h>
#include <stdlib.h>
#include "sum_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int sum_before_and_after_negative(int array[],int array_lenght){
        int between = sum_between_negative(array,array_lenght);
        int sum = 0;
        int i = 0;
        for (i = 0;i < array_lenght;i++){
            sum = sum + abs(array[i]);
        }
        sum = sum - between;
        return sum;
    }