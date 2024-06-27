#include<stdio.h>
#include <time.h>
#include<stdlib.h>
#define SIZE 1000

int compare(const void* a, const void* b) {
	return abs(*(int*)b) - abs(*(int*)a);
}
int	main() {
	int array[SIZE];
	for (int i = 0; i < SIZE; i++)
		scanf("%d",&array[i]);
		
	clock_t start = clock();
	qsort(array, SIZE, sizeof(int), compare);
	clock_t end = clock();
	for (size_t i = 0; i < SIZE; i++)
		printf("%d ", array[i]);
		
	printf("\nsec %f \n", (double)(end-start)/CLOCKS_PER_SEC);
	return 0;
}
