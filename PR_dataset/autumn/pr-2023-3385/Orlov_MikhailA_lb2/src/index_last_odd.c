#include "index_last_odd.h"

int index_last_odd(int* a, int len)
{
	for (int i = len - 1; i >= 0; --i)
	{
		if (a[i] % 2 != 0)
		{
			return i;
		}
	}
}