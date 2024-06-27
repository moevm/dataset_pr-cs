#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define COUNT 1000

int compare_int(const void* a, const void* b);

int main()
{
	int* arr = (int*)malloc(COUNT * sizeof(int));
	time_t t0, t;
	for (int i = 0; i < COUNT; i++) scanf("%d", &arr[i]);
	t0 = clock();
	qsort(arr, COUNT, sizeof(int), (int(*)(const void *, const void *))compare_int);
	t = clock();
	for (int i = 0; i < COUNT; i++) printf("%d ", arr[i]);
	printf("\n%f\n", (double)(t - t0) / CLOCKS_PER_SEC);
	free(arr);
	return 0;
}

int compare_int(const void* a, const void* b)
{
	return *(int*)a <= *(int*)b;
}