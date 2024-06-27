#include "abs_min.h"
int abs_min(int mas[], int ln)
{
	int mn=mas[0];
	for (int i=1; i<ln; i++)
	{
		if (abs(mas[i])<abs(mn))
		{	mn=mas[i];
			}
	}
	return mn;
}
