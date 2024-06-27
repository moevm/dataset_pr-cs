//finds the sum before first minimum
#include "min.h"
int sum(int arr[], int size) {
    int minimum = min(arr, size);
    int sum = 0;
    for (int i = 0; i <= size; i++)
	{
		if (arr[i] != minimum){
			sum += arr[i];
		} else {
			break;
		}
	}
	return sum;
}