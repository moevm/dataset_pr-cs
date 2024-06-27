#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE 1000

int cmp(const void*, const void*);
void input(int[]);
void measureBinarysearch(int[], int);
void measureEnumeration(int[], int);
int* enumerationSearch(int[], int);
void showResult(int*, time_t);

int main() {
    int array[ARR_SIZE];
    input(array);
    qsort(array, ARR_SIZE, sizeof(int), cmp);
    measureBinarysearch(array, 0);
    measureEnumeration(array, 0);
}

int cmp(const void* a, const void* b) {
   return ( *(int*)a - *(int*)b );
}

void input(int array[]) {
    for (int i=0; i<ARR_SIZE; i++) {
        scanf("%d", &array[i]);
    }
}

void showResult(int* result, time_t timeSpent) {
    if (result != NULL) {
        printf("exists\n");
    } else {
        printf("doesn't exist\n");
    }
    printf("%.3f\n", timeSpent/1000.0);
}

void measureBinarysearch(int array[], int target) {
    time_t startBsearch = clock();
    int* result = (int*) bsearch(&target, array, ARR_SIZE, sizeof(int), cmp);
    time_t endBsearch = clock();
    time_t bsearchTime = difftime(endBsearch, startBsearch);
    showResult(result, bsearchTime);
}

void measureEnumeration(int array[], int target) {
    time_t startEnumeration = clock();
    int* result = enumerationSearch(array, target);
    time_t endEnumeration = clock();
    time_t enumerationTime = difftime(endEnumeration, startEnumeration);
    showResult(result, enumerationTime);
}

int* enumerationSearch(int array[], int target) {
    int* result = NULL;
    for (int i=0; i<ARR_SIZE; i++) {
        if (array[i] == target) result = &array[i];
    }
    return result;
}