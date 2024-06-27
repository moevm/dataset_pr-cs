#include "index_last_negative.h"
int index_last_negative(int array[], int count)
{
	
	for(int i = count -1; i>0 ; i--)
	{
		if(array[i] < 0)
		{
			return i-1;
			break;
		}
	}
	return -1;
}
