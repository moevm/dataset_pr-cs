#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
int sum_between_negative(int arr[], int size)
{    int index_first_negative_1 = index_first_negative(arr, size);
     int index_last_negative_1 = index_last_negative(arr, size);
     int sum_between = 0, i;
     for (i = index_first_negative_1; i < index_last_negative_1; i++){
        sum_between += abs(arr[i]);
     }
     return sum_between;  
}  
