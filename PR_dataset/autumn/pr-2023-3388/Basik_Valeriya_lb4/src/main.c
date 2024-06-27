#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const void *a, const void *b) {
    int abs_a = abs(*(int*)a);
    int abs_b = abs(*(int*)b);
    return abs_b - abs_a;
}

int main() {
    int arr[1000];
    srand(time(0));

    for (int i = 0; i < 1000; i++) {
        scanf("%d", &arr[i]); // input array of 1000 integers
    }

    clock_t start = clock();
    qsort(arr, 1000, sizeof(int), cmp);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    for (int i = 0; i < 1000; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("Time taken: %f seconds\n", time_taken);

    return 0;
}
