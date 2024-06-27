#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sorter(const void *a, const void *b){
    const int *i = (const int *)a;
    const int *j = (const int *)b;
    return *i - *j;
    return 0;
}

int main()
{
    int arr[1000];
    int i, j, backward, end_time, start_time, end_time2, start_time2;
    double total, total2;
    start_time = clock();
    for(i = 0; i < 1000; i++){
        scanf("%d", &arr[i]);
    }
    for(i = 0; i < 1000; i++){
        for(j = 0; j < 999; j++){
            if(arr[j] > arr[j + 1]){
                backward = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = backward;
            }
        }
    }
    end_time = clock();
    total = end_time - start_time;

    start_time2 = clock();
    qsort(arr, 1000, sizeof(int), sorter);
    end_time2 = clock();
    total2 = end_time2 - start_time2;
    for(i = 0; i < 1000; i++){
        printf("%d ", arr[i]);
    }
    printf("\n%f", total);
    printf("\n%f", total2);

    return 0;
}