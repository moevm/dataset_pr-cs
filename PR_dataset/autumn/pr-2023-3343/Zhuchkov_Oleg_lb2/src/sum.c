#include "sum.h"
#include "min.h"

int sum(int arr[], int n){
	int minn = min(arr, n), summ = 0, i;
	for (i = 0; i < n; i++)
		if (arr[i] == minn) break;
		else summ += arr[i];
	return summ;	
}
