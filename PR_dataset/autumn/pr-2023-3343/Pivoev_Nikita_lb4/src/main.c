#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define CAPACITY 1000
int compare (const int *i, const int *j){
    return *j - *i;
}

int main(){
    int array[CAPACITY];
    for (int i = 0; i < CAPACITY; ++i)
        scanf("%d", &array[i]);

    clock_t timeCount = clock();
    qsort(array, CAPACITY, sizeof(int), compare);
    timeCount = clock() - timeCount;
    
    for (int i = 0; i < CAPACITY; ++i)
        printf("%d ", array[i]);
    printf("\n%d", timeCount);
    return 0;
}