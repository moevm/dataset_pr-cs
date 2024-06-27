#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp (const void* a, const void* b) {
    const int* f = (const int*)a;
    const int* g = (const int*)b;
    if (abs(*f) > abs(*g)) {
        return -1;
    }
    else if (abs(*f) < abs(*g)) {
        return 1;
    }
    else {
        return 0;
    }
}

int main () {
    int n = 1000;
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    clock_t start_time = clock();
    qsort(arr, n, sizeof(int), cmp);
    clock_t end_time = clock();
    for (int i = 0;i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("%f\n", ((double)(end_time-start_time)/CLOCKS_PER_SEC));
    return 0;
}
