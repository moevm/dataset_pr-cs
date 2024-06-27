#include "abs_max.h"
#include "abs_min.h"

int diff(int input_array[],int input_size){
	int delta = input_array[abs_max(input_array, input_size)] - input_array[abs_min(input_array, input_size)];
	return delta;
}
