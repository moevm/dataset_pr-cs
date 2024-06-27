#include <stdlib.h>
#include "sum_before_even_and_after_odd.h"
#include "index_first_even.h"
#include "index_last_odd.h"

int sum_before_even_and_after_odd(int* a, int len)
{
	int indexEven = index_first_even(a, len);
	int indexOdd = index_last_odd(a, len);

	int sum = 0;
	for (int i = 0; i < indexEven; ++i) sum += abs(a[i]);
	for (int i = indexOdd; i < len; ++i) sum += abs(a[i]);

	return sum;
}