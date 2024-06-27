#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const void* a, const void* b) {
    return *((int*)a) - *((int*)b);
}

void bubblesort(int* arr, size_t n, double* time_spent) {
	clock_t begin = clock();

	for(size_t i = 0; i < n-1; i++) {
		for(size_t j = 0; j < n-i-1; j++) {
			if(arr[j] > arr[j+1]) { 
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
	}

	clock_t end = clock();
	*time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
}

void q_sort(int* arr, double* time_spent) {
	clock_t begin = clock();
	
	qsort(arr, 1000, sizeof(int), cmp);

	clock_t end = clock();
	*time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
}

int main() {
    int* arr = (int*) malloc(1000*sizeof(int));
	double bubble_time_spent;
	double qsort_time_spent;
    
    for(int i=0; i<1000; i++) {
        scanf("%d ", &arr[i]);
    }

    bubblesort(arr, 1000, &bubble_time_spent);
	q_sort(arr, &qsort_time_spent);

	for(int i=0; i<1000; i++)
		printf("%d ", arr[i]);
	printf("\n");

	printf("%f\n", bubble_time_spent);
	printf("%f\n", qsort_time_spent);

	free(arr);
    return 0;
}