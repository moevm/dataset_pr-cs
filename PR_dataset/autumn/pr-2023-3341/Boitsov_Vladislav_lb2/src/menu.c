#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include"index_first_zero.h"
#include"index_last_zero.h"
#include"sum_between.h"
#include"sum_before_and_after.h"
#define ARRAY_SIZE 100
#define ANS "%d\n"

void input(int* array, int* num, int* array_real_size);
void output(int* array, int num, int array_real_size);

int main()
{
	setlocale(LC_ALL, "Rus");
	int array[ARRAY_SIZE];
	int num, array_real_size=0;
	input(array, &num, &array_real_size);
	output(array, num, array_real_size);
	return 0;
}

void input(int* array, int* num, int* array_real_size)
{
	scanf("%d", num);
	char buf;
	do
	{
		scanf("%d%c", &(array[*array_real_size]), &buf);
		
		*(array_real_size)+=1;
	} 
	while (buf != '\n');
}

void output(int* array, int num, int array_real_size)
{
	switch(num)
	{
		case 0:
			printf(ANS, get_index_first_zero(array_real_size, array));
			break;
		case 1:
			printf(ANS, get_index_last_zero(array_real_size, array));
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
}