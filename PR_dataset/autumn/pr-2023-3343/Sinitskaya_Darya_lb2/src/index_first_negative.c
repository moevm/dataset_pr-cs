#include "index_first_negative.h"
int index_first_negative(int *arr_of_integers, int counter)
{
	int f_index=-1; // индекс первого отрицательного элемента
	for(int i=0;i<counter;i++)
	{
        if(arr_of_integers[i]<0)
	     {
		    f_index=i;
		    break;
	     }
	}
	return f_index;
}
