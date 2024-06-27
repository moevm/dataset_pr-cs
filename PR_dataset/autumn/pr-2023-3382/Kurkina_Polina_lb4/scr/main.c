#include <stdlib.h>
#include <stdio.h>
#include <time.h>
int cmp(const void *a, const void *b){
    const int *f = (const int*)a;
    const int *s = (const int*)b;
    if (*f > *s){
        return -1;
    }
    if (*f < *s){
        return 1;
    }
    return 0;
}
int main()
{
    float start = clock();
    int len = 1000;
    int a[len];
    char c;
    for (int i =0; i<len; i++){
        scanf("%d%c", &a[i], &c);
    }
    qsort(a, len, sizeof(int), cmp);
    for (int i =0; i<len; i++){
        printf("%d ", a[i]);
    }
    float end = clock();
    printf("\n%f", (end - start) / (CLOCKS_PER_SEC));
    return 0;
}