#include "Libraries.h"

int index_first_negative(int size, int array[])
{
        for (int i = 0; i < size; i++)
        {
                if (array[i] < 0) return i;
        }
}

