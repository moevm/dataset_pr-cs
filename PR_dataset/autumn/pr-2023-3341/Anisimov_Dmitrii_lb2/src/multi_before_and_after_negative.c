#include "multi_before_and_after_negative.h"
#include "index_first_negative.h"
#include "index_last_negative.h"
#include <stdlib.h>

int multi_before_and_after_negative(int *arr,int counter,int calling_first_function,int calling_second_function){
    int index_four;
    index_four=calling_first_function;
    int s=0;
    int index_five;
    int composition=1;
    for (s=0;s<index_four;s++){
        composition=composition*arr[s];
    }
    for (index_five=calling_second_function;index_five<counter;index_five++){
        composition=composition*arr[index_five];
    }
    return composition;
}