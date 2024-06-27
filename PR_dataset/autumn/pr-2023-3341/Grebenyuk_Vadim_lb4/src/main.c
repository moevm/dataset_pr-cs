#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_LEN 1000

int compare(const void* a, const void* b) {
    return *(int*)b - *(int*)a;
}
void input(int array[ARRAY_LEN]) {
    for (int i = 0; i < ARRAY_LEN; i++)
        scanf("%d", &array[i]);
}

clock_t benchmark(int array[ARRAY_LEN]) {
    clock_t cpu_clocks_start, cpu_clocks_end;
    cpu_clocks_start = clock();
    qsort(array, ARRAY_LEN, sizeof(*array), compare);
    cpu_clocks_end = clock();
    return cpu_clocks_end - cpu_clocks_start;
}

void output(int array[ARRAY_LEN]) {
    for (int i = 0; i < ARRAY_LEN; i++)
        printf("%d ", array[i]);
    putchar('\n');
}

int main() {
    int array[ARRAY_LEN];
    input(array);
    clock_t cpu_clocks_spend = benchmark(array);
    output(array);
    printf("%f\n", cpu_clocks_spend / CLOCKS_PER_SEC);
    return 0;
}
