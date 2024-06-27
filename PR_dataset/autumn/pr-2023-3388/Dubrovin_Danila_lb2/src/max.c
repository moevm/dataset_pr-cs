#include "max.h"

int get_max(int array[], int length)
{
    int max = INT_MIN;
    for(int i = 0; i<length; i++)
    {
        if (array[i]>max)
        {
            max = array[i];
        }
    }
    return max;
}
