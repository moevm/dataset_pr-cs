#include <stdio.h>
#include "call_operation.h"
#include "filling_the_array.h"
#define N 101

int main()
{
	int count;
	int array[N];
	filling_the_array(array, &count);
	call_operation(array, count);
}
