#include "index_last_zero.h"

int index_last_zero(int arr[], int size){
	int last_index = -1;
	for (int i = size - 1; i >= 0; --i){
		if (arr[i] == 0){
			last_index = i;
			break;
		}
	}
	return last_index;
}
