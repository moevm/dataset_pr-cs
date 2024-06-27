#include "index_last_negative.h"
int index_last_negative(int lenght, int array[]){
	int i = 0;
	int right;
		for (i; i < lenght; i++){
			if (array[i] < 0){
				right = i;
			}
	}
	return right;
}