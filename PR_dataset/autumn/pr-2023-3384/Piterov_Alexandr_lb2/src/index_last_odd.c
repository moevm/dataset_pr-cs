#include "index_last_odd.h"

int index_last_odd(int* arr, int len){
	
	int index = -1;
	for(int i = len - 1; i >= 0; i--){
		
		if(arr[i] % 2 != 0){
			index = i;
			break;
		}
	}

	return index;
}

