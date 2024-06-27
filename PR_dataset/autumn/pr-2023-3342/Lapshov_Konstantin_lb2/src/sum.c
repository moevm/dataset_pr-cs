#include "sum.h"
#include "abs_max.h"

int sum(int array_num[], int length){
    int max_num = abs_max(array_num, length);
    int sum = 0;

    for (int i = 0; i < length; i++) {
        if(max_num == array_num[i]){
            for (int j = i; j < length; j++) {
                sum += array_num[j];
            }
            return sum;
        }
    }
}