#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 1000

void input(int* arr);
int cmp(const void* firstEl, const void* secondEl);
void searchByFunc(int* arr);
int searchByBrutForce(int* arr);
void output(int* bsearchRes, double long timeBsearch);
void freeMem(int** arr);

int main() {
    int* arr = (int*)malloc(sizeof(int) * ARRAY_SIZE);

    input(arr);

    qsort(arr, ARRAY_SIZE, sizeof(int), cmp);

    searchByFunc(arr);

    searchByBrutForce(arr);

    freeMem(&arr);
    return 0;
}

void input(int* arr) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        scanf("%d", &(arr[i]));
    }
}

int cmp(const void* firstEl, const void* secondEl) {
    int* first = (int*) firstEl;
    int* second = (int*) secondEl;
    if (*first > *second) return 1;
    if (*first < *second) return -1;
    return 0;
}

void searchByFunc(int* arr) {
    int zero = 0;

    clock_t startTime = clock();
    int* zeroSearch = (int*)bsearch(&zero, arr, ARRAY_SIZE, sizeof(int), cmp);
    clock_t endTime = clock();

    double long timeUsedForSearch = ((double long) (endTime - startTime)) / CLOCKS_PER_SEC;

    output(zeroSearch, timeUsedForSearch);
}

int searchByBrutForce(int* arr) {
    clock_t startTime = clock();
    int found = 0;

    for (int i = 0; i < ARRAY_SIZE; i++) {
        if (arr[i] == 0) {
            found = 1;
            break;
        }
    }

    clock_t endTime = clock();
    double long timeUsedForSearch = ((double long) (endTime - startTime)) / CLOCKS_PER_SEC;

    output(found ? &found : NULL, timeUsedForSearch);

    return found;
}

void output(int* bsearchRes, double long timeBsearch) {
    if (bsearchRes != NULL) {
        printf("exists\n");
        printf("%Lf\n", timeBsearch);
    } else {
        printf("doesn't exist\n");
    }
}

void freeMem(int** arr) {
    free(*arr);
}
