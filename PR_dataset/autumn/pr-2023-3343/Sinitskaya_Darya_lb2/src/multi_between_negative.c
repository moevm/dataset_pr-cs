#include "multi_between_negative.h"
#include"index_first_negative.h"
#include"index_last_negative.h"
int multi_between_negative(int *arr_of_integers, int counter)
{
	int f1_index=index_first_negative(arr_of_integers, counter); // индекс первого отрицательного э-та массива
	int l1_index=index_last_negative(arr_of_integers, counter); // инидекс последнего отрицательного э-та массива
	int composition=1; // произведение искомых э-тов массива
	for(int i=f1_index;i<l1_index;i++)
	{
		composition*=arr_of_integers[i];
	}
	return composition;
}
