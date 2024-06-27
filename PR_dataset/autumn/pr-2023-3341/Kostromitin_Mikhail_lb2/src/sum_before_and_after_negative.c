#include "Libraries.h"
#include "index_first_negative.h"
#include "index_last_negative.h"

int sum_before_and_after_negative(int size, int array[])
{
        int sum = 0;

        for (int i = 0; i < index_first_negative(size, array); i++)
        {
                sum += abs(array[i]);
        }
        for (int i = index_last_negative(size, array); i < size; i++)
        {
                sum += abs(array[i]);
        }

        return sum;
}
