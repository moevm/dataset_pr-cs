#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const void *a, const void *b){
    const int *f = (const int *)a;
    const int *s = (const int *)b;
    if (*f > *s){
        return 1;
    }
    if (*f < *s){
        return -1;
    }
    return 0;
}

int main()
{
    int n = 1000;
    int mas[n];
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &mas[i]);
    }
    qsort(mas, n, sizeof(int), cmp);
    int null = 0;
    clock_t start_search = clock();
    int *res = (int*) bsearch(&null, mas, n, sizeof(int),cmp);
    clock_t end_search = clock();
    double search_time = ((double) (end_search - start_search)) / CLOCKS_PER_SEC;
    if (res){
        printf("exists\n");
    }
    else{
        printf("doesn't exist\n");
    }
    printf("%lf\n", search_time);
    int flag = 0;
    clock_t start_search_1 = clock();
    for(int i = 0; i < n; i++)
    {
        if (mas[i] == 0){
            printf("exists\n");
            flag = 1;
            break;
        }
    }
    clock_t end_search_1 = clock();
    double search_time_1 = ((double) (end_search_1 - start_search_1)) / CLOCKS_PER_SEC;
    if(flag == 0){
        printf("doesn't exist\n");
    }
    printf("%lf", search_time_1);
    return 0;
}
