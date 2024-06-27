#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubbleSort(int arr[],int size){
    for (int i = 0; i < size -1 ; i++){
        for (int j = 0; j < size - i -1 ; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int cmp(const void* a, const void* b) {
    const int* f = (const int*)a;
    const int* g = (const int*)b;

    return *f - *g;
}

void qsort_func(int arr[], int size) {
    qsort(arr, size , sizeof(int), cmp);
}

int main() {
    const int size =1000;
    int arr[size];
    int arr_q[size];

    for (int i = 0; i < size; i++) {
        int a;
        scanf("%d", &a);
        arr[i] = a;
        arr_q[i] = a;
    }

    double time_bubble = 0.0;
    clock_t begin_bubble = clock();
    bubbleSort(arr,size);
    clock_t end_bubble = clock();
    time_bubble += (double)(end_bubble - begin_bubble) / CLOCKS_PER_SEC;

    double time_quick = 0.0;
    clock_t begin_quick = clock();
    qsort_func(arr_q,size);
    clock_t end_quick = clock();
    time_quick += (double)(end_quick - begin_quick) / CLOCKS_PER_SEC;

    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("%lf\n", time_bubble);
    printf("%lf\n", time_quick);

    return 0;
}
