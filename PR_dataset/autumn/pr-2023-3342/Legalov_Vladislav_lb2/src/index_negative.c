#include "index_negative.h"
int index_negative(int *arr, int size, int dir){
	int i = 0;
	if (dir < 0)
		i = size - 1;
	for (; (i < size) && (i > -1); i = i + dir){
		if (arr[i] < 0)
			return i;
	}
	return -1;
}
