#include <stdio.h>      // IO
#include <stdlib.h>     // bsearch
#include <search.h>     // lfind
#include <time.h>       // struct timespec, clock_gettime

#define ARR_LEN 1000llu
int arr[ARR_LEN];

int intcmp(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}

int* solve_bsearch()
{
    int key = 0;
    return bsearch(&key, arr, ARR_LEN, sizeof(*arr), intcmp);
}

int* solve_bruteforce()
{
    int key = 0;
    size_t arr_len = ARR_LEN;
    return lfind(&key, arr, &arr_len, sizeof(*arr), intcmp);
}

void measure_exec_time(int* (*func_ptr)())
{
    struct timespec time_start;
    struct timespec time_end;
    int *res;

    clock_gettime(CLOCK_MONOTONIC, &time_start); 
    res = func_ptr();
    clock_gettime(CLOCK_MONOTONIC, &time_end);
    
    puts((res == NULL) ? "doesn't exist" : "exists");
    printf("%ld nanoseconds\n", (time_start.tv_sec*1000000000 + time_end.tv_nsec) - (time_end.tv_sec*1000000000 + time_start.tv_nsec));
}

int main()
{
    for (int i = 0; i < ARR_LEN; i++)
        scanf("%d", &arr[i]);

    qsort(arr, ARR_LEN, sizeof(*arr), intcmp);
    
    measure_exec_time(solve_bsearch);
    measure_exec_time(solve_bruteforce);
}