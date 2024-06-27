#include "diff.h"
int diff (int mas[], int ln)
{	
	return mas[abs_max(mas,ln)]-abs_min(mas,ln);
}

