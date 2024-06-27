#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"

int sum_before_and_after_negative(int arr[], int size){
    //сумма модулей эл. массива (до 1-го отриц. (не вкл. эл.) и после послед. отриц. (вкл. эл.))
    int index_first = index_first_negative(arr, size);
    int index_last = index_last_negative(arr, size);
    int summ = 0;
    for(int i=0; i < index_first; i++){
        summ += abs(arr[i]);
    }
    for(int i = index_last; i<size; i++){
        summ += abs(arr[i]);
    }
    return summ;
}
