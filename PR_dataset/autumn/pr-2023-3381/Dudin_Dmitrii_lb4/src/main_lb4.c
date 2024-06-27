#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFFER 100500
#define N 1000

int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

double measure_time(int (*func)(int nums[N], int target), int nums[N], int target) {
    clock_t start = clock();
    int result = func(nums, target);
    clock_t end = clock();
    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

    if (result)
        printf("exists\n");
    else
        printf("doesn't exist\n");

    printf("%f\n", elapsed_time);

    return elapsed_time;
}

int binary_search(int nums[N], int target) {
    void *bin_res = bsearch(&target, nums, N, sizeof(int), compare);
    return bin_res != NULL;
}

int linear_search(int nums[N], int target) {
    for (int i = 0; i < N; i++) {
        if (nums[i] == target) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char input[BUFFER];
    fgets(input, BUFFER, stdin);
    char *p = input;

    int nums[N];
    for (int i = 0; i < N; i++) {
        nums[i] = strtol(p, &p, 10);
    }
    qsort(nums, N, sizeof(int), compare);

    int search_target = 0;

    measure_time(binary_search, nums, search_target);
    measure_time(linear_search, nums, search_target);

    return 0;
}
