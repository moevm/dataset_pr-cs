#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int cmp(const void *a, const void *b){
	const int* f = (const int*)a;
	const int* s = (const int *)b;
	if(*f > *s)
	    return 1;
	if(*f < *s)
		return -1;
	return 0;
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int main() {
    int arr[1000];
    
    for (int i = 0; i < 1000; i++){
        scanf("%d", &arr[i]);
    }
    
    clock_t start_bubble = clock();
    bubbleSort(arr, 1000);
    clock_t end_bubble = clock();
    double time_bubble = (double)(end_bubble - start_bubble) / CLOCKS_PER_SEC;
    
    clock_t start_quick = clock();
    qsort(arr, 1000, sizeof(int), cmp);
    clock_t end_quick = clock();
    double time_quick = (double)(end_quick - start_quick) / CLOCKS_PER_SEC;
    
    for (int i = 0; i < 1000; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    printf("%f\n", time_bubble);
    printf("%f\n", time_quick);
    
    return 0;
}
