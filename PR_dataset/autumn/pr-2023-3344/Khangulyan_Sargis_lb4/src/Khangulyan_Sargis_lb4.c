#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long double Bsort(int *arr);
long double Qsort(int *arr);
int compare(const void *key, const void *cmp_elm);

int main(){
    int arr_1[1000];
    int arr_2[1000];
    for (int i=0; i<1000; i++){
        scanf("%d", &arr_1[i]);
        arr_2[i] = arr_1[i];
    }

    long double Bsort_time = Bsort(arr_1);
    long double Qsort_time = Qsort(arr_2);

    for (int i=0; i<1000; i++){
        printf("%d ", arr_1[i]);
    }
    printf("\n%Lf\n%Lf", Bsort_time, Qsort_time);
    return 0;
}

long double Bsort(int *arr){
    clock_t begin = clock();
    for (int k=0; k<999; k++){
        for (int n=0; n<999-k; n++){
            if (arr[n] > arr[n+1]){
                int temp = arr[n];
                arr[n] = arr[n+1];
                arr[n+1] = temp;
            }
        }
    }
    clock_t end = clock();
    return (long double) (end - begin) / CLOCKS_PER_SEC;
}

long double Qsort(int *arr){
    clock_t begin = clock();
    qsort(arr, 1000, sizeof(int), compare);
    clock_t end = clock();
    return (long double) (end - begin) / CLOCKS_PER_SEC;
}

int compare(const void *key, const void *cmp_elm){
    return (*(int*)key - *(int*)cmp_elm);
}