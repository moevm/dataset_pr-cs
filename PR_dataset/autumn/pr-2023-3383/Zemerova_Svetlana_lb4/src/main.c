#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 1000
int cmp(const void* a,const void* b);
clock_t sortbubble(void* mas);
clock_t quicksort(void* mas);

int cmp(const void* a,const void* b){
    const int* f=(const int*)a;
    const int* s=(const int*)b;
    if (*f>*s) return 1;
    if (*f<*s) return -1;
    return 0;
}

clock_t sortbubble(void* a){
    int *mas=(int*)a;
    int buf,f;
    clock_t t=clock();
    for (size_t j=0; j<N-1; j++){
        f=0;
        for (size_t i=0; i<N-j-1; i++){
            if (mas[i]>mas[i+1]){
                buf=mas[i];
                mas[i]=mas[i+1];
                mas[i+1]=buf;
                f=1;
            }
        }
        if (f==0) break;
    }
    return clock()-t;
}

clock_t quicksort(void* a){
    int *mas=(int*)a;
    clock_t t=clock();
    qsort(mas,N,sizeof(int),cmp);
    return clock()-t;
}

int main(){
    int mas[N],mas2[N];
    for (size_t i=0; i<N; i++){
        scanf("%d", &mas[i]);
        mas2[i]=mas[i];
    }
    clock_t timebubble=sortbubble(mas);
    clock_t timeqsort=quicksort(mas2);
    for (size_t i=0; i<N; i++){
        printf("%d ", mas[i]);
    }
    printf("\n");
    printf("Сортировка пузырьком: %f секунд.\n",(double)timebubble/CLOCKS_PER_SEC);
    printf("Быстрая сортировка: %f секунд.\n",(double)timeqsort/CLOCKS_PER_SEC);
}
