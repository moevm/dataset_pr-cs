#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

int compar(const void *a, const void *b){
    const int *n1 = (const int *) a;
    const int *n2 = (const int *) b;
    if (*n1 < *n2) {
        return 1;
    } else if (*n1 > *n2){
        return -1;
    }
    return 0;
}

int main(){
    int *mas = (int *) malloc(N * sizeof(int));
    for (size_t i = 0; i < N; i++){
        scanf("%d ", &mas[i]);
    }
    clock_t begin = clock();
    qsort(mas, N, sizeof(int), compar);
    clock_t end = clock();
    for (size_t i = 0; i < N; i++) {
        printf("%d ", mas[i]);
    }
    printf("\n%lf", ((double) (end - begin)) / CLOCKS_PER_SEC);
    free(mas);
    return 0;
}
