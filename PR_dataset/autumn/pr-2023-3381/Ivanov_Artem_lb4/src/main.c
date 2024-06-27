#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE 1000

int compare(const void* a, const void* b)
{
    if (abs(*(int*)a) < abs(*(int*)b))
    {
        return 1;
    }
    else if (abs(*(int*)a) > abs(*(int*)b)) {
        return -1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    int* arr = (int*)malloc(ARR_SIZE*sizeof(int));
    
    // заполнение массива чисел
    for (size_t i = 0; i < ARR_SIZE; i++)
    {
        scanf("%d", &arr[i]);
    }
    
    clock_t time_of_start = clock();
    qsort(arr, ARR_SIZE, sizeof(int), compare);
    clock_t time_of_end = clock();
    
    time_t runtime = time_of_end - time_of_start;
    
    for (size_t i = 0; i < ARR_SIZE; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("%c", '\n');
    printf("qsort runtime in seconds: [%f]\n", (double)runtime/CLOCKS_PER_SEC);

    free(arr);
    return 0;
}
