#include "index_last_negative.h"
int index_last_negative(int *arr_of_integers, int counter)
{
	int l_index=-1; // индекс последнего отрицательного элемента
	for(int i=counter-1;i>-1;i--)
	{
		if(arr_of_integers[i]<0)
		{
			l_index=i;
			break;
		}
	}
	return l_index;
}
