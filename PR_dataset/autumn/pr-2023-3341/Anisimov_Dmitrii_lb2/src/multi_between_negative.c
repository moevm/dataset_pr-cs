#include "multi_between_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
#include <stdlib.h>

int multi_between_negative(int *arr,int counter,int calling_first_function,int calling_second_function){
    int index_three;
    int multiplication=1;
    for (index_three=calling_first_function;index_three<calling_second_function;index_three++){
        multiplication=multiplication*arr[index_three];
    }
    return multiplication;
}