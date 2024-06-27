#include "index_first_even.h"

int index_first_even(int arr[], int size_arr){
int index = 0;
    for (int i=0;i<size_arr;i++)
    	{
    	   if (abs(arr[i]) % 2 == 0)
    		{
    			int index = i;
       			return index;
    		}    	
	}
}
