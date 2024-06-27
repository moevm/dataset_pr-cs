//problem 3
#include <stdlib.h>
#include <stdio.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"

int main()
{
	//reading mode and array from stdin
	int mode = 0;
	int arr_len = 0;
	int arr[100];
	char delimiter;
	scanf("%d", &mode);
	delimiter = getchar();
	for(arr_len = 0; arr_len < 100 && delimiter == ' '; arr_len++)
	{
		scanf("%d", &arr[arr_len]);
		delimiter = getchar();
	}

	//find selected value
	switch(mode)
	{
		case 0:
			printf("%d\n", index_first_zero(arr, arr_len));
			break;

		case 1:
			printf("%d\n", index_last_zero(arr, arr_len));
			break;

		case 2:
			printf("%d\n", sum_between(arr, arr_len));
			break;

		case 3:
			printf("%d\n", sum_before_and_after(arr, arr_len));
			break;

		default:
			printf("Данные некорректны\n");
			break;
	}
	return 0;
}
