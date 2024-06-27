#include "index_first_negative.h"

int index_first_negative(int *array, int length)
{
	for(int i = 0; i < length; i++)
	{
		if(array[i] < 0)
		return i;
	}
    return -1;
}
