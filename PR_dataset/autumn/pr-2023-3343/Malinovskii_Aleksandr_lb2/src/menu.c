#include <stdio.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_before_even_and_after_odd.h"
#include "sum_between_even_odd.h"
#define MAX_SIZE 100
int main()
{
	//function number input
	int choice;
	scanf("%d", &choice);

	//array input
	int array[MAX_SIZE];
	int size_updated = 0;
	while (getchar() != '\n')
	{
		scanf("%d", &array[size_updated]);
		size_updated++;
	}
	
	//switching functions
	switch (choice)
	{
	case 0:
		printf("%d", index_first_even(array, size_updated));
		break;

	case 1:
		printf("%d", index_last_odd(array, size_updated));
		break;

	case 2:
		printf("%d", sum_between_even_odd(array, size_updated));
		break;
	case 3:
		printf("%d", sum_before_even_and_after_odd(array, size_updated));
		break;
	default:
		printf("Данные некорректны");
		break;
	}
}
