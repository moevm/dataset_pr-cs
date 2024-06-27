#include <stdlib.h>
#include <stdio.h>
#include <time.h>

const int n = 1000;

void bubble_sort (int* s){
    
    int tmp;
    for (int i = 0; i < n; ++i){
        for (int j = 0; j < n - 1; ++j){
            if (s[j] > s[j + 1]){
                tmp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = tmp;
            }
            
        }
    }
    for (int i = 0; i < n; ++i){
        printf("%d ", s[i]);
    }
    puts("");
}


int cmp(const void *a, const void *b){
    const int *f = (const int*) a;
    const int *s = (const int*) b;
    if (*f > *s)
        return 1;
    if (*f < *s)
        return -1;
    return 0;
    
}
int main(){
    __clock_t tb;
    int s[n];
    for (int i = 0; i < n ; i++){
        scanf("%d ", &s[i]);
    }

    tb = clock();

    bubble_sort(s);

    tb = clock() - tb;
    printf("time -> %f\n", (float)tb/CLOCKS_PER_SEC);


    __clock_t tq;
    tq = clock();
    qsort(s, n, sizeof(int), cmp);
    tq = clock() - tq;
    printf("time -> %f\n", (float)tq/CLOCKS_PER_SEC);
    
    return 0;
}

