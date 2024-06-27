#include "abs_max.h"
int abs_max(int mas[], int ln)
{	int mx=mas[0];
	int mxi=0;
	for (int i=1; i<ln; i++)
	{
		if (abs(mas[i])>abs(mx))
		{	mx=mas[i];
			mxi=i;	
			}
	}
	return mxi;
}

