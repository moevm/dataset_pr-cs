#include "index_first_negative.h"
int index_first_negative(int array[], int count)
{

	for(int i=0; i<count; i++)
	{
		if(array[i] < 0)
		{
			return i-1;
			break;
		}
	}
	return -1;
}
