#include "index_first_zero.h"
#include "index_last_zero.h"
#include <stdlib.h>
int sum_between(int massive[], int i, int len)
{
    int sum_b = 0;
    int lower = index_first_zero(massive, i, len);
    int upper = index_last_zero(massive, i, len);
    for(i = lower; i < upper; i++)
    {
        sum_b += abs(massive[i]);
    }
    return sum_b;
}
