#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int compare(const void* a, const void* b) {
    return (*(int *) a - *(int *) b);
}



int main(){
    int mass[1000];
    for(int i = 0;i<1000;i++){
        scanf("%d",&mass[i]);
    }
    int target = 0;
    int test  =mass[999];
    clock_t start = clock();
    qsort(mass,1000,sizeof(int),compare);
    int* result = (int*)bsearch(&target,mass,1000,sizeof(int),compare);
    clock_t end = clock();
    double timesec = (double)(end-start)/CLOCKS_PER_SEC;
    if (result != NULL){
        printf("exists\n");
        printf("sec = %f\n",timesec);
    }
    if (result == NULL){
        printf("doesn't exist\n");
    }
    int resb = 0;
    clock_t start2 = clock();
    for(int i = 0;i<1000;i++){
        if (mass[i] == 0){
            resb = 1;
        }
    }
    clock_t end2 = clock();
    double timesec2 = (double)(end2-start2)/CLOCKS_PER_SEC;
    if (resb == 1){
        printf("exists\n");
        printf("sec = %f\n",timesec2);
    }
    if (resb == 0){
        printf("doesn't exist\n");
    }


}