#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comp(const int *a, const int *b)
{
    return *a - *b;
}

double time_spent(clock_t begin, clock_t end)
{
    return (double)(end - begin) / CLOCKS_PER_SEC;
}

int main()
{
    srand(time(NULL));

    const int length = 1000;
    int array[length];
    for (int i = 0; i < length; i++)
    {
        int temp = 0;
        scanf("%d", &temp);
        array[i] = temp;
    }

    qsort(array, length, sizeof(int), (int (*)(const void *, const void *))comp);

    int key = 0;

    clock_t begin = clock();
    int *null_flag_bin = bsearch(&key, array, length, sizeof(int), (int (*)(const void *, const void *))comp);
    clock_t end = clock();

    printf(null_flag_bin ? "exists\n" : "doesn't exist\n");
    printf("%lf\n", time_spent(begin, end));

    int null_flag_n = 0;
    begin = clock();
    for (int i = 0; i < length; i++)
    {
        if (array[i])
            continue;
        null_flag_n = 1;
        break;
    }
    end = clock();
    printf(null_flag_n ? "exists\n" : "doesn't exist\n");
    printf("%lf\n", time_spent(begin, end));
}