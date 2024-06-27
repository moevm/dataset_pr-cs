#include <stdio.h>
#include "sum_before_and_after.h"
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sumAbs.h"
int sumBeforeAndAfter(int array[], int lenghtArray){
	int startFirst = 0;
	int startSecond = indexLastZero(array, lenghtArray);
	int endFirst = indexFirstZero(array, lenghtArray);
	int endSecond = lenghtArray - 1;
	if (startSecond < 0) return -1;
	return sumAbs(array, startFirst, endFirst) + sumAbs(array, startSecond, endSecond);
}
