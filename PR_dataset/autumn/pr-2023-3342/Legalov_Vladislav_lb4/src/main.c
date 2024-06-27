#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000
const int SIZE_INT = sizeof(int);

int comparator_non_increase(const void *first, const void *second){
	int first_value = abs(*((int*)first));
	int second_value = abs(*((int*)second));
	if (first_value < second_value) return 1;
	if (first_value > second_value) return -1;
	return 0;
}
void fill_array_of_int(int *array, int size){
	for (int i = 0; i < size; ++i)
		scanf("%d", &array[i]);
}
void print_array(int *array, int size){
	for (int i = 0; i < size; ++i)
		printf("%d ", array[i]);
}

int main(){
	int array[SIZE];
	fill_array_of_int(array, SIZE);
	
	clock_t count_clocks = clock();
	qsort(array, SIZE, SIZE_INT, comparator_non_increase);
	count_clocks = clock() - count_clocks;
	
	print_array(array, SIZE);
	printf("\n%f\n", (float)count_clocks / (float)CLOCKS_PER_SEC);
	return 0;
}
