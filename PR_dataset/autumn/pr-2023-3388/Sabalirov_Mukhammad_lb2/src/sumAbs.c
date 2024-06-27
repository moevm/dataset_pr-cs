#include <stdio.h>
#include <stdlib.h>
#include "sumAbs.h"
int sumAbs(int array[], int start, int end){
	int sum = 0;
	for (int i = start; i <= end; i++) sum += abs(array[i]);
	return sum;
}
