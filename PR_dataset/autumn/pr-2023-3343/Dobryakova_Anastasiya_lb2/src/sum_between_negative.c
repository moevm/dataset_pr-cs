#include <stdio.h>
#include <stdlib.h>
#include "index_first_negative.h"
#include "index_last_negative.h"

int sum_between_negative(int arr[], int size){
    //сумма модулей эл. массива (от 1-го отриц. (вкл. эл.) и до послед. отриц. (не вкл. эл.))
    int index_first = index_first_negative(arr, size);
    int index_last = index_last_negative(arr, size);
    int summ = 0;
    for(int i = index_first; i < index_last; i++){
        summ += abs(arr[i]);
    }
    return summ;
}
