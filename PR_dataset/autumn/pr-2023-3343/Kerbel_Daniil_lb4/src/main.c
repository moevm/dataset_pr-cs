#define SIZE 1000


#include<stdio.h>

#include<stdlib.h>

#include <time.h>

int relate_elements(const void* a, const void* b) {
    
	return abs(*(int*)b) - abs(*(int*)a);
	
}
void main() {
    
	int arrange[SIZE];
	
	for (int i = 0; i < SIZE; i++)
	
		scanf("%d",&arrange[i]);
		
	clock_t start = clock();
	
	qsort(arrange, SIZE, sizeof(int), relate_elements);
	
	clock_t end = clock();
	
	for (size_t i = 0; i < SIZE; i++)
	
		printf("%d ", arrange[i]);
		
	printf("\nsec %f \n", (double)(end-start)/CLOCKS_PER_SEC);
	
}