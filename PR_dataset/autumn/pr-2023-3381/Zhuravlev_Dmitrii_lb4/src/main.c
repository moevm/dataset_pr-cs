#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void *a, const void *b)
{
   const int *A = a, *B = b;
   return (*A > *B) - (*A < *B);
}

void swap(int* arr, int i, int j) 
{ 
    int temp = arr[i]; 
    arr[i] = arr[j]; 
    arr[j] = temp; 
} 
  
void bubble_sort(int arr[], int n) 
{ 
    int i, j; 
    for (i = 0; i < n - 1; i++) 
        for (j = 0; j < n - i - 1; j++) 
            if (arr[j] > arr[j + 1]) 
                swap(arr, j, j + 1); 
} 

int main() {
    int arr1[1000];
    int arr2[1000];
    double start, end;
    for (int i = 0;i < 1000; i++) {
        scanf("%d",&arr1[i]);
        arr2[i] = arr1[i];
    }

    start = clock();
    qsort(arr1, sizeof(arr1)/sizeof(int), sizeof(int), compare);
    end = clock();
    double qsort_time = end - start;

    start = clock();
    bubble_sort(arr2, sizeof(arr2)/sizeof(int));
    end = clock();
    double bubble_time = end - start;

    for (int i = 0; i < 1000; i++){
        printf("%d ", arr1[i]);
    }
    printf("\n%f\n%f\n", bubble_time, qsort_time);
    return 0;
}
