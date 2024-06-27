#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_LEN 1000

int compare(const void *a, const void *b);
int linearSearch(int *key, int *array, size_t array_len);

int main()
{
    int array[ARRAY_LEN];
    int key_to_find = 0;

    for (size_t i = 0; i < ARRAY_LEN; ++i)
    {
        scanf("%d", &array[i]);
    }

    qsort(array, ARRAY_LEN, sizeof(int), compare);

    // бинарный поиск
    clock_t bsearch_start, bsearch_end;
    double bsearch_time_used;

    char *bsearch_result;

    bsearch_start = clock();
    int *bsearch_index = bsearch(&key_to_find, array, ARRAY_LEN, sizeof(int), compare);
    bsearch_end = clock();

    bsearch_time_used = difftime(bsearch_end, bsearch_start) / CLOCKS_PER_SEC;

    if (bsearch_index != NULL)
        bsearch_result = "exists";
    else
        bsearch_result = "doesn't exist";

    // линейный поиск
    clock_t linear_start, linear_end;
    double linear_time_used;

    char *linear_result;

    linear_start = clock();
    int linear_index = linearSearch(&key_to_find, array, ARRAY_LEN);
    linear_end = clock();

    linear_time_used = difftime(linear_end, linear_start) / CLOCKS_PER_SEC;

    if (linear_index != -1)
        linear_result = "exists";
    else
        linear_result = "doesn't exist";

    printf("%s\n%lf\n%s\n%lf\n", bsearch_result, bsearch_time_used, linear_result, linear_time_used);
    return 0;
}

int compare(const void *a, const void *b)
{
    const int *a1 = (const void *)a;
    const int *b1 = (const void *)b;

    if (*a1 > *b1)
        return 1;
    if (*a1 < *b1)
        return -1;
    return 0;
}

int linearSearch(int *key, int *array, size_t array_len)
{
    for (size_t i = 0; i < array_len; ++i)
        if (array[i] == *key)
            return i;
    return -1;
}