#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define ARRAY_SIZE 1000

int compare_ints(const void* a, const void* b)
{
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
 
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

void bubble_sort(int* arr, int arr_size)
{
        int sort_done = 0;
        for(int last = arr_size-1; last > 0; last--) {
                int moved = 0;
                for(int i = 0; i < last; i++) {
                        if(arr[i] > arr[i+1]) {
                                int tmp = arr[i];
                                arr[i] = arr[i+1];
                                arr[i+1] = tmp;
                                moved = 1;
                        }
                }
                if(!moved) {break;}
        }
}

int main()
{
        //input reading
        int arr_bubble[ARRAY_SIZE];
        int arr_qsort[ARRAY_SIZE];
        for(int i = 0; i < ARRAY_SIZE; i++) {
                scanf("%d", &arr_bubble[i]);
                arr_qsort[i] = arr_bubble[i];
        }

        //sorting with bubble
        clock_t start = clock();
        bubble_sort(arr_bubble, ARRAY_SIZE);
        clock_t end = clock();
        float bubble_sort_time = (start-end)/CLOCKS_PER_SEC;

        //sorting with qsort
        start = clock();
        qsort(arr_qsort, ARRAY_SIZE, sizeof(int), compare_ints);
        end = clock();
        float qsort_sort_time = (start-end)/CLOCKS_PER_SEC;

        //displaying results
        for(int i = 0; i < ARRAY_SIZE; i++) {printf("%d ", arr_bubble[i]);}
        printf("\n%f\n%f\n", bubble_sort_time, qsort_sort_time);
        return 0;
}
