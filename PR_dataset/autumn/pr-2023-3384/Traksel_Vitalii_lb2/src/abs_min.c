#include <stdlib.h>

int abs_min (int input_array[],int input_size){
	int min = 0;
	for (int count = 1; count<input_size; count++){
		if (abs(input_array[min]) > abs(input_array[count])) min = count; 
	}
	return (min);
}
