#include "index_first_negative.h"
int index_first_negative(int lenght, int array[]){
	int i = 0;
	int left;
	for (i; i < lenght; i++){
		if (array[i] < 0){
			left = i;
			break;
		}
	}
	return left;
}