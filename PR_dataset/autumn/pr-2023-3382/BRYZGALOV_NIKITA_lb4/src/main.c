#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define size 1000

int cmp(const void* num1_, const void* num2_) {
    int num1 = *((int *) num1_);
    int num2 = *((int *) num2_);
    if (abs(num1) > abs(num2)) return -1;
    else if (abs(num1) == abs(num2)) return 0;
    else return 1;
}

int main()
{
    int *array = malloc(sizeof(int) * size);
    char symbol;
    for (int i = 0; i < size; i ++) 
        scanf("%d%c", &array[i], &symbol);
    time_t start = clock();
    qsort(array, size, sizeof(int), cmp);
    double passed_time = ((clock() - start) / CLOCKS_PER_SEC);
    for (int i = 0; i < size; i ++) 
        printf("%d ", array[i]);
    printf("\n%f\n", passed_time);
    return 0;
}
