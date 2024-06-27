#include "sum.h"

#include "global.h"
#include "stdlib.h"

int sum(int start, int end) {
    int sum = 0;
    for (int i = start; i < end; i++)
        sum += abs(nums[i]);
    return sum;
}