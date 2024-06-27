#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define RAZMER 1000
int sravn(const void* a, const void* b) {
    return (*(int *) a - *(int *) b);
}
int main(){
    int massiv[RAZMER];
    for(int i=0;i<RAZMER;i++){
        scanf("%d",&massiv[i]);
    }
    int simvol = 0;
    int test = massiv[RAZMER-1];
    clock_t nach = clock();
    qsort(massiv,RAZMER,sizeof(int),sravn);
    int* resultat = (int*)bsearch(&simvol,massiv,RAZMER,sizeof(int),sravn);
    clock_t kon = clock();
    double tf = (double)(kon-nach)/CLOCKS_PER_SEC;
    if (resultat != NULL){
        printf("exists\n");
        printf("sec = %f\n",tf);
    }
    if (resultat == NULL){
        printf("doesn't exist\n");
    }
    int k = 0;
    clock_t nach2 = clock();
    for(int i = 0;i<RAZMER;i++){
        if (massiv[i] == 0){
            k = 1;
        }
    }
    clock_t kon2 = clock();
    double tf2 = (double)(kon2-nach2)/CLOCKS_PER_SEC;
    if (k == 1){
        printf("exists\n");
        printf("sec = %f\n",tf2);
    }
    if (k == 0){
        printf("doesn't exist\n");
    }
}
