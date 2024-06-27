#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#include "macros.h"
#include "min.h"
#include "max.h"
#include "diff.h"
#include "sum.h"


int main()
{
	char input[MAX_LEN];
	fgets(input, MAX_LEN, stdin);
	char *p = input;
	int nums[SIZE];
	int input_length = 0;
	while(*p)
	{
		if (isdigit(*p) || ((*p=='-'||*p=='+') && isdigit(*(p+1))))
		{
			nums[input_length++] = strtol(p, &p, 10);
		}
		else
		{
			p++;
		}
	}
	
	switch(nums[0])
	{
		case 0: // max.c
			printf("%d\n", nums[max_index(nums, 1, input_length)]);
			break;
		case 1: // min.c
			printf("%d\n", nums[min_index(nums, 1, input_length)]);
			break;
		case 2: // diff.c
			printf("%d\n", diff(nums, 1, input_length));
			break;
		case 3: // sum.c
			printf("%d\n", sum(nums, 1, input_length));
			break;
		default: // error
			printf("Данные некорректны\n");
	}
	return 0;
}

