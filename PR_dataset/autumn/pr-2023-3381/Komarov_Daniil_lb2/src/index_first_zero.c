#include "index_first_zero.h"
int index_first_zero(int arr[], int arr_len)
{
	for(int i = 0; i < arr_len; i++)
	{
		if(arr[i] == 0) {return i;}
	}
	return 0;  //program will never reach this point, nevertheless I've added this line to prevent compiler warning 
}
