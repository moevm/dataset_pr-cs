#include <stdio.h>
#include "max.h"

int max(int* arr, int len){

	int max = -100000;
	for (int i = 0; i < len; i++){
 
	    if (max < arr[i]){
  
			max = arr[i];
		}
	}
	return max;
}
