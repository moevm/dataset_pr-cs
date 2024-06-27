#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"

int sum_between_negative(int array[],int array_lenght) {
        int sum = 0;
        int first_index = index_first_negative(array,array_lenght);
        int last_index = index_last_negative(array,array_lenght);
        while (first_index < last_index) {
            sum = sum + abs(array[first_index]);
            first_index++;
        }
        return sum;
    }