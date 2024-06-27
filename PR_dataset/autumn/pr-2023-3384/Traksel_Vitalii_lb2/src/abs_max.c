#include <stdlib.h>

int abs_max (int input_array[],int input_size){
	int max = 0;
	for (int count = 1; count<input_size; count++){
		if (abs(input_array[max]) < abs(input_array[count])) max = count; 
	}
	return(max);
}
