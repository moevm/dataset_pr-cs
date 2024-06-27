#include "abs_max.h"

int sum(int input_array[],int input_size){
	int total_sum = 0;
	int index = abs_max(input_array, input_size);
	for(index; index<input_size; index++){
		total_sum += input_array[index];
	}
	return(total_sum);
}
