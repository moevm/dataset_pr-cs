#include <stdio.h>
#include "filling_the_array.h"
#define N 101


int filling_the_array(int array[], int *count)
{
	*count = 0;
	do
	{
		if(*count<N)
		{
			scanf("%d", &array[*count++]);
			
		}
	}
	while(getchar() !='\n');
	
}
