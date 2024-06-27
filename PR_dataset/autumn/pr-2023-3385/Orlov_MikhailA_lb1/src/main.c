#include <stdio.h>
#include <stdlib.h>

int index_first_even(int* a, int len)
{
	for (int i = 0; i < len; ++i)
	{
		if (abs(a[i]) % 2 == 0)
		{
			return i;
		}
	}
}

int index_last_odd(int* a, int len)
{
	for (int i = len - 1; i >= 0; --i)
	{
		if (abs(a[i]) % 2 != 0)
		{
			return i;
		}
	}
}

int sum_between_even_odd(int* a, int len)
{
	int e = 1;
	int indexEven = 0, indexOdd = 0;
	
	for (int i = 0; i < len; ++i)
	{
		if (e && abs(a[i]) % 2 == 0)
		{
			indexEven = i;
			e = 0;
		}
		if (abs(a[i]) % 2 != 0) indexOdd = i - 1;
	}

	int sum = 0;
	for (int i = indexEven; i <= indexOdd; ++i) sum += abs(a[i]);

	return sum;
}

int sum_before_even_and_after_odd(int* a, int len)
{
	int e = 1;
	int indexEven = 0, indexOdd = 0;
	for (int i = 0; i < len; ++i)
	{
		if (e && abs(a[i]) % 2 == 0)
		{
			indexEven = i;
			e = 0;
		}
		if (abs(a[i]) % 2 != 0) indexOdd = i;
	}

	int sum = 0;
	for (int i = 0; i < indexEven; ++i) sum += abs(a[i]);
	for (int i = indexOdd; i < len; ++i) sum += abs(a[i]);

	return sum;
}

int main()
{
	int k = 0;
	int mode;
	int arr[100];
	char c;

	scanf("%d", &mode);
	for (int i = 0; i < 100; ++i)
	{
		scanf("%d%c", &arr[i], &c);
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