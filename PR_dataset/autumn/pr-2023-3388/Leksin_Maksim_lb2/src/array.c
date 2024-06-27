#include "array.h"

int input_array(int arr[N]) {
	int size = 0;
        char space =' ';
        while (size < N && space == ' ') {
                scanf("%d%c", &arr[size], &space);
                size++;
        }
	return size;
}	
