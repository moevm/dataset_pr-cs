#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const void *key, const void *base)
{
    const int *a = (const int *)key;
    const int *b = (const int *)base;
    return (*a - *b);
}
int main()
{
    int array[1000], len = 0, key = 0, s2 = 0;
    char symbol;
    while (1)
    {
        scanf("%d", &array[len++]);
        symbol = getchar();
        if (symbol == '\n' || len == 1000)
            break;
    }
    qsort(array, len, sizeof(int), cmp);
    clock_t start_time1 = clock(); // время начала бинпоиска
    int *s1 = bsearch(&key, array, len, sizeof(int), cmp);
    clock_t finish_time1 = clock(); // время конца бинпоиска
    if (s1 != NULL)
    {
        printf("exists\n");
    }
    else
    {
        printf("doesn't exist\n");
    }
    printf("%ld\n", finish_time1 - start_time1);
    clock_t start_time2 = clock(); // время начала поиска перебором
    for (int i = 0; i < len; i++)
    {
        if (array[i] == key)
        {
            s2 = 1;
        }
    }
    clock_t finish_time2 = clock(); // время конца поиска перебором
    if (s2 != 0)
    {
        printf("exists\n");
    }
    else
    {
        printf("doesn't exist\n");
    }
    printf("%ld\n", finish_time2 - start_time2);
}