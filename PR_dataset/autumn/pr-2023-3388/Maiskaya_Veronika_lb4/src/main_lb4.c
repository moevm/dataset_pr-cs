#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

int compareInt(const void *firstNum, const void *secondNum)
{
    if (*((int *)firstNum) < *((int *)secondNum))
        return 1;
    else if (*((int *)firstNum) > *((int *)secondNum))
        return -1;
    else
        return 0;
}

void inputArr(int array[], int size)
{
    for (int i = 0; i < size; i++)
        scanf("%d", &array[i]);
}

void printArr(int array[], int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

void sortArr(int array[], int size, clock_t *startTime, clock_t *endTime)
{
    *startTime = clock();

    qsort(array, size, sizeof(int), compareInt);

    *endTime = clock();
}

void printTime(clock_t startTime, clock_t endTime)
{
    double sortTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
    printf("%lf", sortTime);
}

int main()
{
    int array[SIZE];

    inputArr(array, SIZE);

    clock_t startTime, endTime;
    sortArr(array, SIZE, &startTime, &endTime);

    printArr(array, SIZE);

    printTime(startTime, endTime);

    return 0;
}
