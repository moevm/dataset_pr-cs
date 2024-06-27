#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

void input(int array[],int* ptr_len){

    char space = ' ';

    while (*ptr_len < SIZE && space == ' ') {
        scanf("%d%c", &array[*ptr_len], &space);
        *ptr_len = *ptr_len + 1;
        }

}

int comp(const void *a, const void *b) {
    const int *f = (const int *)a; 
    const int *s = (const int *)b;
    if (*f > *s) {
        return 1;
    } else if (*f < *s) {
        return -1;
    }
    return 0;
}




void time_binary_search(int array[])
{
    int target = 0;
    int* result;
    clock_t start_time, end_time;
    double binary_search_time;


    
    
 
    start_time = clock();
    result = (int*) bsearch(&target, array, SIZE, sizeof(int), comp);
    end_time = clock();
    binary_search_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;


    if (result) {
        printf("exists\n");
    } else {
        printf("doesn't exist\n");
    }
    printf("%f\n", binary_search_time);

}

void time_linear_search(int array[])
{

    double linear_search_time;
    int target = 0;   

    clock_t start_time, end_time;


    int res = -1;

    start_time = clock();
    for (int i = 0; i < SIZE; i++)
    {
        if (array[i] == target) 
        {
            res = i;
            break;
        }
    }
    end_time = clock();
    linear_search_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;


    if (res != -1) {
        printf("exists\n");
    } else {
        printf("doesn't exist\n");
    }
    printf("%f\n", linear_search_time);
}


int main() {
    int array[SIZE];
    int len = 0;
    int* ptr_len = &len;
    input(array, ptr_len);


    qsort(array, sizeof(array) / sizeof(int), sizeof(int), comp);
    time_binary_search(array);
    time_linear_search(array);
    return 0;
}
