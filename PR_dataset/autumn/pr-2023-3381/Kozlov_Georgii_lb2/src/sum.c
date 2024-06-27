#include <stdio.h>
#include "min.h"

int sum(int array[100], int len){
    int min_num = min(array, len);
    int summ = 0;
    for (int i = 0; i < len; i++){
        if (array[i] == min_num){
            break;
        }
        summ += array[i];
    }
    return summ;
}
