#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000
int sort_puz(int *array){
    int tmp;
    int change;
    for (int i = SIZE - 1; i >= 0; i--)
    {
        change = 1;
        for (int j = 0; j < i; j++)
        {
            if (array[j] > array[j + 1])
            {
                tmp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = tmp;
                change = 0;
            }
        }
        if (change == 1)
            break;
    }
}
int comparison(const int *i, const int *j){
    return *i - *j;
}
int main() {
    int array[SIZE];
    int arr[SIZE];
    int i;
    clock_t start, end;
    double time_used1, time_used2;
    for (i = 0; i < SIZE; i++) {
        scanf("%d", &array[i]);
    }
    int j;
    for (j = 0; j < SIZE; j++) {
        arr[j] = array[j];
    }
    start = clock();
    sort_puz(arr);
    end = clock();
    time_used1 = ((double) (end - start)) / CLOCKS_PER_SEC;
    start = clock();
    qsort(array, SIZE, sizeof (int), (int(*) (const void *, const void *))comparison);
    end = clock();
    time_used2 = ((double) (end - start)) / CLOCKS_PER_SEC;
    int k;
    for (k = 0; k < SIZE; k++) {
        printf("%d ", array[k]);
    }
    printf("\n");
    printf("%f %f", time_used1, time_used2);
}
