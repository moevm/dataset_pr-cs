#include "sum.h"
int sum (int mas[], int ln)
{	int s=0;
	for (int i=abs_max(mas,ln);i<ln;i++)
	{
		s+=mas[i];
	}
	return s;
}

