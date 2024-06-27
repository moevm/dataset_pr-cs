#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ARRAY_LENGTH 1000

int cmp(const void *a, const void *b) {
    int f = *((int *) a);
    int s = *((int *) b);
    if (f > s) {
        return -1;
    } else if (f < s) {
        return 1;
    }
    return 0;
}

int main(void) {
    int *nums = (int *) malloc(ARRAY_LENGTH * sizeof(int));
    for (size_t i = 0; i < ARRAY_LENGTH; i++) {
        scanf("%d", &nums[i]);
    }
    
    clock_t start = clock();
    qsort(nums, ARRAY_LENGTH, sizeof(int), cmp);
    clock_t end = clock();

    for (size_t i = 0; i < ARRAY_LENGTH; i++) {
        printf("%d ", nums[i]);
    }
    
    printf("\n");
    printf("%f", ((float) (end - start)) / CLOCKS_PER_SEC);

    return 0;
}

