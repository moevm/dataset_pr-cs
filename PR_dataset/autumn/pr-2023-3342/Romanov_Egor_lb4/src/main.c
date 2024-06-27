#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define ARR_SIZE 1000

int cmp(const void *a, const void *b){
    const int *first = (const int*)a;
    const int *second = (const int*)b;

    if (*first>*second){
        return 1;
    }
    if (*first<*second){
        return -1;
    }
    return 0;
}

void fill_array(int *arr){
    for (int i=0;i<ARR_SIZE;i++){
        scanf("%d",&arr[i]);
    }
}

int print_existance(int exist){
    if (exist){
        printf("exists\n");
    } else{
        printf("doesn't exist\n");
    }
}

int find_zero_slow(int *arr){
    int res = 0;
    for (size_t i =0;i<ARR_SIZE;i++){
        if (arr[i] == 0){
            res = 1;
            break;
        }
    }
    return res;
}

int find_zero_fast(int *arr){
    int key = 0;
    int* res = (int*)bsearch(&key, arr, ARR_SIZE, sizeof(int),cmp);
    if (res){
        return 1;
    }
    return 0;
}

double get_process_time(int (*process)(int *arr), int *arr){
    clock_t start_time, end_time;
    start_time = clock();
    process(arr);
    end_time = clock();
    
    return (double)(((double) (end_time - start_time)) / CLOCKS_PER_SEC);
}

void give_answer(int *arr){
    print_existance(find_zero_fast(arr));
    printf("%f\n", get_process_time(find_zero_fast,arr));

    print_existance(find_zero_slow(arr));
    printf("%f\n", get_process_time(find_zero_slow,arr));
}

int main(){
    int arr[ARR_SIZE];
    fill_array(arr);
    qsort(arr, ARR_SIZE, sizeof(int), cmp);
    give_answer(arr);
    return 0;
}
