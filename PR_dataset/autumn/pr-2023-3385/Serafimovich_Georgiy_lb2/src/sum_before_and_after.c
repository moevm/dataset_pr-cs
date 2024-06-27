#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"

int sum_before_and_after(int* arr, int l){
        int first = index_first_zero(arr,l);
        int last = index_last_zero(arr,l);
        int sum1 = 0;
        int sum2 = 0;
        for(int i = 0;i < first;i++)
                sum1 += abs(arr[i]);
        for(int i = last;i < l;i++)
                sum2 += abs(arr[i]);
        int sum = sum1 + sum2;
        return sum;
}
