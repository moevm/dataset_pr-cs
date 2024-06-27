#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_QUANTITY 1000

void input_data(int *arr_first, int *arr_second);
void output_data(int *arr_first, clock_t first_time, clock_t second_time);
void free_arr(int *arr_first, int *arr_second);
void bubble_sort(int *arr);
int cmp(const void* a, const void* b);

int main() {
    int *arr_first = malloc(MAX_QUANTITY * sizeof(int));
    int *arr_second = malloc(MAX_QUANTITY * sizeof(int));

    input_data(arr_first, arr_second);

    clock_t begin_first = clock();
    bubble_sort(arr_first);
    clock_t end_first = clock();

    clock_t begin_second = clock();
    qsort(arr_second,MAX_QUANTITY,sizeof(int),cmp);
    clock_t end_second = clock();

    output_data(arr_first, (begin_first - end_first), (begin_second - end_second));
    free_arr(arr_first, arr_second);

    return 0;
}

void input_data(int *arr_first, int *arr_second){
    for (int i = 0; i < MAX_QUANTITY; i++){
        scanf("%d", &arr_first[i]);
    }

    for (int i = 0; i < MAX_QUANTITY; i++) {
        arr_second[i] = arr_first[i];
    }
}
void output_data(int *arr_first, clock_t first_time, clock_t second_time){

    for (int i = 0; i < MAX_QUANTITY; ++i) {
        printf("%d ", arr_first[i]);
    }

    printf("\n%f", (double)(first_time));
    printf("\n%f", (double)(second_time));
}
void free_arr(int *arr_first, int *arr_second){
    free(arr_first);
    free(arr_second);
}
void bubble_sort(int *arr){
    int tmp;
    int no_swap;

    for (int i = MAX_QUANTITY - 1; i >= 0 ; i--) {
        no_swap = 1;

        for (int j = 0; j < i; j++) {
            if(arr[j] > arr[j + 1]){
                tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
                no_swap = 0;
            }
        }

        if (no_swap == 1) {
            break;
        }
    }
}
int cmp(const void* a, const void* b){
    const int* first = (const int*) a;
    const int* second = (const int*) b;

    if (*first  >= *second ){
        return -1;
    }
    if (*first  < *second ){
        return 1;
    }
    return 0;
}