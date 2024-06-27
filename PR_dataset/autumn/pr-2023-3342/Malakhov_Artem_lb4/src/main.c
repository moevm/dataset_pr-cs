#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE_ARRAY 1000

void fill_arrays(int *first_array, int *second_array, int size_arr){
	for (int i = 0; i < size_arr; i++)
		scanf("%d", &first_array[i]);
    memcpy(second_array, first_array, sizeof(int)*size_arr);
}

void bubbleSort(int* array, int size_arr)
{
    for (int i = 0; i < size_arr-1; i++){
        for (int j = 0; j <  size_arr-i-1; j++){
            if (array[j] > array[j + 1]){
                int temporary = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temporary;
            }
        }
    }
}

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

int* get_sort_times(double* time_bublesort, double* time_qsort, int array_for_bublesort[], int array_for_qsort[], int size_arr)
{
    *time_bublesort = clock();
    bubbleSort(array_for_bublesort, size_arr);
    *time_bublesort = clock() - *time_bublesort;

    *time_qsort = clock();
    qsort(array_for_qsort, size_arr, sizeof(int), compare);
    *time_qsort = clock() - *time_qsort;
}

void print_array(int arr[], int size_arr)
{
    for (int i = 0; i < size_arr; i++)
        printf("%d ", arr[i]);
}

void output(int array_for_bublesort[], clock_t time_bublesort, clock_t time_qsort)
{
    print_array(array_for_bublesort, SIZE_ARRAY);
	printf("\n%f\n", (float)time_bublesort / CLOCKS_PER_SEC);
    printf("%f\n", (float)time_qsort / CLOCKS_PER_SEC);
}

int main()
{
	int array_for_bublesort[SIZE_ARRAY];
    int array_for_qsort[SIZE_ARRAY];
    clock_t time_bublesort;
    clock_t time_qsort;

	fill_arrays(array_for_bublesort, array_for_qsort, SIZE_ARRAY);
    get_sort_times(&time_bublesort, &time_qsort, array_for_bublesort, array_for_qsort, SIZE_ARRAY);
	output(array_for_bublesort, time_bublesort, time_qsort);

	return 0;
}