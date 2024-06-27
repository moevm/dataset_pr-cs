#include <stdio.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"

int main()
{
	int k = 0;
	int mode;
	int arr[100];
	char c;

	scanf_s("%d", &mode);
	for (int i = 0; i < 100; ++i)
	{
		scanf_s("%d%c", &arr[i], &c);
		++k;
		if (c == '\n') break;
	}


	if (mode == 0) printf("%d\n", index_first_even(arr, k));
	else if (mode == 1) printf("%d\n", index_last_odd(arr, k));
	else if (mode == 2) printf("%d\n", sum_between_even_odd(arr, k));
	else if (mode == 3) printf("%d\n", sum_before_even_and_after_odd(arr, k));
	else printf("Данные некорректны\n");
	return 0;
}