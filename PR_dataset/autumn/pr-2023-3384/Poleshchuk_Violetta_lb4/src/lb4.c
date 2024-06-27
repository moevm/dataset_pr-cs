#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define LEN 1000

void input(int* array){
    for (int index = 0; index < LEN; index++){
        scanf("%d", &array[index]);
    }
}

int cmp(const void *a, const void *b){
    const int *first_number=(const int *)a;
    const int *second_number=(const int *)b;
    if (*first_number < *second_number)
        return -1;
    else if (*first_number > *second_number)
        return 1;
    return 0; 
}

void first_method(int* first_array){
    clock_t start_time = clock();
    int key = 0;
    int* result = (int*)bsearch(&key, first_array, LEN, sizeof(int), cmp);
    clock_t end_time = clock();
    float time_used = (float)(start_time - end_time);
    if (result){
        printf("%s\n%f\n", "exists", time_used);
    }else{
        printf("%s\n%f\n", "doesn't exist", time_used);
    }
}

void second_method(int* array){
    clock_t start_time = clock();
    float time_used;
    for (int index = 0; index < LEN; index++){
        if (array[index] == 0){
            clock_t end_time = clock();
            time_used = (float)(start_time - end_time);
            printf("%s\n%f\n", "exists", time_used);
            return;
        }
    }
    printf("%s\n%f\n", "doesn't exist", time_used);
}

int main(){
    int first_array[LEN];
    input(first_array);
    int second_array[LEN];
    memcpy(second_array, first_array, sizeof(first_array));
    qsort(first_array, LEN, sizeof(int), cmp);
    first_method(first_array);
    second_method(second_array);
}