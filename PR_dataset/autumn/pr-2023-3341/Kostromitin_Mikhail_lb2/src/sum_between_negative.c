#include "Libraries.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int sum_between_negative(int size, int array[])
{
        int sum = 0;

        for (int i = index_first_negative(size, array); i < index_last_negative(size, array); i++)
        {
                sum += abs(array[i]);
        }

        return sum;
}

