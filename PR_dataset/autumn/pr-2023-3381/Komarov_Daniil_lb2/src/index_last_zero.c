#include "index_last_zero.h"
int index_last_zero(int arr[], int arr_len)
{
	for(int i = arr_len-1; i >= 0; i--)
	{
		if(arr[i] == 0) {return i;}
	}
	return 0;  //program will never reach this point, nevertheless I've added this line to prevent compiler warning 
}
