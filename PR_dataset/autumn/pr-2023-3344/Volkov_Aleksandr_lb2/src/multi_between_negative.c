#include "index_first_negative.h"
#include "index_last_negative.h"

int multi_between_negative(int numbers[], int size){
	int index_first = index_first_negative(numbers, size);
	int index_last = index_last_negative(numbers, size);
	int multiplication = 1;
	for(int i = index_first; i < index_last; i++){
		multiplication *= numbers[i]; 
	}
	return multiplication;
}