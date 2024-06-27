#include "index_first_even.h"

int index_first_even(int* a, int len)
{
	for (int i = 0; i < len; ++i)
	{
		if (a[i] % 2 == 0)
		{
			return i;
		}
	}
}