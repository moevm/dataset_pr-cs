#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 101
#define MAX_LEN 1000


int min_index(int nums[SIZE], int start, int stop)
{
	int	res = 10005000,
		ind = -1;
	
	for(int i = start; i < stop; i++)
	{
		if(res > nums[i])
		{
			res = nums[i];
			ind = i;
		}
	}
	return ind;
}


int max_index(int nums[SIZE], int start, int stop)
{
	int	res = 0,
		ind = -1;
	
	for(int i = start; i < stop; i++)
	{
		if(res < nums[i])
		{
			res = nums[i];
			ind = i;
		}
	}
	return ind;
}


void main()
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
	
	int a, b, sum, stop;
	switch(nums[0])
	{
		case 0: // max
			printf("%d\n", nums[max_index(nums, 1, input_length)]);
			break;
		case 1: // min
			printf("%d\n", nums[min_index(nums, 1, input_length)]);
			break;
		case 2: // diff
			a = nums[max_index(nums, 1, input_length)];
			b = nums[min_index(nums, 1, input_length)];
			printf("%d\n", a - b);
			break;
		case 3: // sum
			sum = 0;
			stop = min_index(nums, 1, input_length);
			for(int n = 1; n < stop; n++)
			{
				sum += nums[n];
			}
			printf("%d\n", sum);
			break;
		default: // error
			printf("Данные некорректны\n");
	}
}

