#include "index_first_negative.h"
#include "index_last_negative.h"

int sum_before_and_after_negative(int numbers[], int size){
    int sum_before_and_after=0;
    int first_negative=index_first_negative(numbers, size);
    int last_negative=index_last_negative(numbers, size);

    for(int i = 0;i < first_negative; i++){
        sum_before_and_after=sum_before_and_after+abs(numbers[i]);
    }

    for(int i = last_negative;i < size; i++){
        sum_before_and_after=sum_before_and_after+abs(numbers[i]);
    }

    return sum_before_and_after;
}
