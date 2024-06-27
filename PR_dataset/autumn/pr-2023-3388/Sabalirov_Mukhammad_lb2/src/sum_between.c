#include <stdio.h>
#include "sum_between.h"
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sumAbs.h"
int sumBetween(int array[], int lenghtArray){
	int indexFirstZero = indexFirstZero(array, lenghtArray);
        int indexLastZero = indexLastZero(array, lenghtArray);
	if (start < 0) return -1;
	return sumAbs(array, indexFirstZero, indexLastZero);
}
