#include "sum_before_even_and_after_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"

int sum_before_even_and_after_odd(int arr[], int len){
    int answer = 0;
    int i;
    for (i = 0; i < index_first_even(arr, len); i++){
        answer = answer + abs(arr[i]);
    }
    for (i = index_last_odd(arr, len); i < len; i++){
        answer = answer + abs(arr[i]);
    }
    return answer;
};

