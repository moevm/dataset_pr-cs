#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
int sum_between_even_odd(int arr[100]){
	int index1=0;
	int index2=0;
	int sum=0;
	int i;
        index1=index_first_even(arr);
        index2=index_last_odd(arr);
	for(i=index1;i<index2;i++){
		sum+=abs(arr[i]);
	}
	return sum;
}
