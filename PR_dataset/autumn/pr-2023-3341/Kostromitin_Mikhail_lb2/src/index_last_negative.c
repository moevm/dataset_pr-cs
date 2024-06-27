#include "Libraries.h"

int index_last_negative(int size, int array[])
{
        for (int i = size - 1; i >= 0; i--)
        {
                if (array[i] < 0) return i;
        }
}
