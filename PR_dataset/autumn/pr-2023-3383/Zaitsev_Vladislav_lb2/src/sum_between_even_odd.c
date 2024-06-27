#include "sum_between_even_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"

int sum_between_even_odd(int arr[], int len){
    int answer = 0;
    int i;
    for (i = index_first_even(arr, len); i < index_last_odd(arr, len); i++){
            answer = answer + abs(arr[i]);
        }
    return answer;
};

