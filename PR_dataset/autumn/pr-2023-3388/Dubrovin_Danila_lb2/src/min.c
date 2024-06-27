#include "min.h"

int get_min(int array[], int length)
{
    int min = INT_MAX;
    for(int i = 0; i<length; i++)
    {
        if (array[i]<min)
        {
            min = array[i];
        }
    }
    return min;
}
