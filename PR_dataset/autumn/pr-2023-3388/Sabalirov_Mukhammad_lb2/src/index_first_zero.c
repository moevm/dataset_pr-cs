#include <stdio.h>
#include "index_first_zero.h"
int indexFirstZero(int array[], int lenghtArray){
	for (int i=0; i<lenghtArray; i++){
		if (array[i] == 0) return i;
	}
	return -1;
}
