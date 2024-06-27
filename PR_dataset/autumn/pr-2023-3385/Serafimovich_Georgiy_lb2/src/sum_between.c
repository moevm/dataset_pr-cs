#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"

int sum_between(int* arr,int l){
        int first = index_first_zero(arr,l);
        int last = index_last_zero(arr,l);
        int sum = 0;
        for(int i = first;i < last;i++)
                sum += abs(arr[i]);
        return sum;
}
