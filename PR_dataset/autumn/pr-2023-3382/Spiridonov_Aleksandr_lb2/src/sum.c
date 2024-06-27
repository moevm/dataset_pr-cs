#include <stdio.h>

#include "min.h"

int sum(int* arr, int len){
 
	int mn = min(arr, len);
	int sum = 0;
	int i = 0;

	while (arr[i] != mn){
 
		sum += arr[i];
		i += 1;
	}
	return sum;
}
