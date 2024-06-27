#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_before_and_after_negative(int numbers[], int size){
	int index_first = index_first_negative(numbers, size);
	int index_last = index_last_negative(numbers, size);
	int multiplication = 1;
	for(int i = 0; i < index_first; i++){
		multiplication *= numbers[i];
	}
	for(int i = index_last; i<size; i++){
		multiplication *= numbers[i];
	}
	return multiplication;
}