#include "data_reading.h"
#include "print_solve.h"
#define MAX_SIZE_ARR 20

int main(){
	int array[MAX_SIZE_ARR];
	int operation = -1;
	int array_count_items = 0;
	data_reading(array, &operation, &array_count_items);
	print_solve(array, operation, array_count_items);
	return 0;
}
