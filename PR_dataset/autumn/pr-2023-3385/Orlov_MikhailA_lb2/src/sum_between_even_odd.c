#include <stdlib.h>
#include "sum_between_even_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"

int sum_between_even_odd(int* a, int len)
{
	int indexEven = index_first_even(a, len);
	int indexOdd = index_last_odd(a, len) - 1;

	int sum = 0;
	for (int i = indexEven; i <= indexOdd; ++i) sum += abs(a[i]);

	return sum;
}