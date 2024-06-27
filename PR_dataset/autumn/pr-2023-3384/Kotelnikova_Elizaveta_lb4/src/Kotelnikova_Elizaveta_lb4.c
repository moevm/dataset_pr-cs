#include<stdio.h>
#include<stdlib.h>
#include <time.h>
int comr(const void* a, const void* b){
    const int* f= (const int*)a;
    const int* s= (const int*)b;
    if (abs(*f)<abs(*s)){
        return 1;
        }
    if (abs(*f)>abs(*s)){
        return -1;
    }
    return 0;
}
int main(){
    int arr[1000];
    double tme=0.0;
    for (int i=0; i<1000; ++i){
        scanf("%d", &arr[i]);}
    clock_t begin = clock();
    qsort(arr, 1000, sizeof(int), comr);
    clock_t end = clock();
    for (int j=0; j<1000; ++j){
        printf("%d ", arr[j]);
        }
    tme += (double)(end-begin) / CLOCKS_PER_SEC;
    printf("\n%f", tme);
}