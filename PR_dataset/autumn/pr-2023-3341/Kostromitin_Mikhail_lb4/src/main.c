#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZEOFARR 1000

void input(int* arr);
int cmp(const void* firstEl, const void* secondEl);
void searchByFunc(int* arr);
int searchByBrutForce(int* arr);
void output(int* bsearchRes, double long timeBsearch);
void freeMem(int** arr);

int main()
{
    int* arr = (int*)malloc(sizeof(int) * SIZEOFARR);

    input(arr);

    qsort(arr, SIZEOFARR, sizeof(int), cmp);

    searchByFunc(arr);

    searchByBrutForce(arr);

    freeMem(&arr);
    return 0;
}


void input(int* arr)
{
    for (int i = 0; i < SIZEOFARR; i++)
    {
        scanf("%d", &(arr[i]));
    }
}


int cmp(const void* firstEl, const void* secondEl)
{
    int* first = (int*) firstEl;
    int* second = (int*) secondEl;
    if (*first > *second) return 1;
    if (*first < *second) return -1;
    return 0;

}


void searchByFunc(int* arr)
{
    int zero = 0;

    clock_t startTime = clock();
    int* zeroSearch = (int*)bsearch(&zero, arr, SIZEOFARR, sizeof(int), cmp);
    clock_t endTime = clock();

    double long timeUsedForSearch = ((double long) (endTime - startTime)) / CLOCKS_PER_SEC;

    output(zeroSearch, timeUsedForSearch);
}


int searchByBrutForce(int* arr)
{
    clock_t startTime = clock();
    for (int i = 0; i < SIZEOFARR; i++)
    {
        if (arr[i] == 0)
        {
            clock_t endTime = clock();
            double long timeUsedForSearch = ((double long) (endTime - startTime)) / CLOCKS_PER_SEC;
            int flag = 1;
            output(&flag, timeUsedForSearch);
            return 1;
        }
    }
    output(NULL, 1);
}


void output(int* bsearchRes, double long timeBsearch)
{
    if (bsearchRes != NULL)
    {
        printf("exists\n");
        printf("%Lf\n", timeBsearch);
    }
    else printf("doesn't exist\n");
}


void freeMem(int** arr)
{
    free(*arr);
}
