#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define SIZE 1000

int cmp(const void *a, const void *b) {
	const int *f = (const int*)a;
	const int *s = (const int*)b;
	if (abs(*f) > abs(*s)) {
		return -1;
	}
	if (abs(*f) < abs(*s)) {
		return 1;
	}
	return 0;
}

clock_t sort_time(int* arr)
{
	clock_t timestart = clock();
	qsort(arr, SIZE, sizeof(int), cmp);
	clock_t timeend = clock();
	return timeend - timestart;
}

int input(int *arr) {
	for (int i = 0; i < SIZE; i++) {
		scanf("%d", &arr[i]);
	}
}

int output(int *arr) {
	for (int i = 0; i < SIZE; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main()
{
	int arr[SIZE];
	input(arr);
	clock_t sort = sort_time(arr);
	output(arr);
	printf("%ld", sort);
	return 0;
}
