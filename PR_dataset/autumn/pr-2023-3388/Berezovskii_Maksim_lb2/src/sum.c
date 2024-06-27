#include "sum.h"
#include "abs_max.h"

int sum(int array[], int len, int index_max){
    int total = 0;
    for (int i = index_max; i < len; i++){
        total += array[i];
    }
    return total;
}

