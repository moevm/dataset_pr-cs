#include "index_first_zero.h"

int index_first_zero(int arr[], int size){
	int first_index = -1;
	for (int i = 0; i < size; ++i){
		if (arr[i] == 0) {
			first_index = i;
			break;			
		}
	}
	return first_index;
}
