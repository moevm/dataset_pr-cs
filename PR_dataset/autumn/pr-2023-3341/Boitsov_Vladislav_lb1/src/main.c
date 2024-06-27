#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#define ARRAY_SIZE 100

int get_index_first_zero(int array_real_size, int array[])
{
	for(int i=0;i<array_real_size;i++)
	{
		if(array[i]==0)
		{
			return i;
		}
	}
}
int get_index_last_zero(int array_real_size, int array[])
{
	for(int i=array_real_size-1;i>=0;i--)
	{
		if(array[i]==0)
		{
			return i;
		}
	}
	
}

void print_sum_between(int array_real_size, int array[])
{
	int sum=0;
	for(int i=get_index_first_zero(array_real_size, array); i<get_index_last_zero(array_real_size, array);i++)
		sum+=abs(array[i]);
	printf("%d\n", sum);
}

void print_sum_before_and_after(int array_real_size, int array[])
{
	int sum=0;
	for(int i=0;i<get_index_first_zero(array_real_size, array);i++)
		sum+=abs(array[i]);
	for(int i=get_index_last_zero(array_real_size, array);i<array_real_size;i++)
		sum+=abs(array[i]);
	printf("%d\n", sum);
}

int main()
{
	setlocale(LC_ALL, "Rus");
	int array[ARRAY_SIZE];
	int num=0, array_real_size=0;
	scanf("%d", &num);
	char buf;
	do
	{
		scanf("%d%c", &array[array_real_size], &buf);
		array_real_size++;
	} 
	while (buf != '\n');
	switch(num)
	{
		case 0:
			printf("%d\n", get_index_first_zero(array_real_size, array));
			break;
		case 1:
			printf("%d\n", get_index_last_zero(array_real_size, array));
			break;
		case 2:
			print_sum_between(array_real_size, array);
			break;
		case 3:
			print_sum_before_and_after(array_real_size, array);
			break;
		default:
			printf("Данные некорректны\n");
	}
	return 0;
}

