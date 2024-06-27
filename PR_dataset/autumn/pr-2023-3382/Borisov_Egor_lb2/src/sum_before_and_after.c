
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"


int sum_before_and_after(int massive[], int i, int len)
{
    int sum_b_a = 0;
    int lower = index_first_zero(massive, i, len);
    int upper = index_last_zero(massive, i, len);
    for(i = 0; i < lower; i++)
    {
        sum_b_a += abs(massive[i]);
    }
    for(i = upper; i < len; i++)
    {
        sum_b_a += abs(massive[i]);
    }
    return sum_b_a;
}
