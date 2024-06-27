#include "index_first_negative.h"
#include "index_last_negative.h"

int sum_between_negative(int numbers[], int size){
    int sum_between=0;
    int first_negative=index_first_negative(numbers, size);
    int last_negative=index_last_negative(numbers, size);

    for(int i = first_negative;i < last_negative; i++){
        sum_between=sum_between+abs(numbers[i]);
    }

    return sum_between;
}
