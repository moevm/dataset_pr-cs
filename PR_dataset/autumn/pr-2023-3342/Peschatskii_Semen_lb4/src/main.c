#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000
#define OUTPUT_FORMAT "%s\n"
const int SIZE_INT = sizeof(int);
int comparator(const void *f, const void *s){
    int first_num = *((int*)f);
    int second_num = *((int*)s);
    if (first_num < second_num){return 1;}
    if (first_num > second_num){return -1;}
    return 0;
}
void bsearch_time(int key, int arr[]){
    clock_t count_tic_bsearch=clock();
    int *zero_existence=bsearch(&key, arr, SIZE, SIZE_INT, comparator);
    count_tic_bsearch = clock() - count_tic_bsearch;
    if(zero_existence==NULL){printf(OUTPUT_FORMAT,"doesn't exist");}
    else{printf(OUTPUT_FORMAT,"exists");}
    printf("%ld\n",count_tic_bsearch);
}
void cicle_time(int key, int arr[]){
    int zero_pos=SIZE+1;
    clock_t count_tic_cicle=clock();
    for(int i=0; i<SIZE;i++){
        if(arr[i]==0){zero_pos=i; break;}
    }
    count_tic_cicle=clock()-count_tic_cicle;
    if(key<=SIZE){printf(OUTPUT_FORMAT,"doesn't exist");}
    else{printf(OUTPUT_FORMAT,"exists");}
    printf("%ld\n",count_tic_cicle);
}
int main(){
    int arr[SIZE];
    for (int i =0; i<SIZE; i++){
        scanf("%d", &arr[i]);
    }
    qsort(arr, SIZE, SIZE_INT, comparator);
    int key=0;
    bsearch_time(key, arr);
    cicle_time(key, arr);
    return 0;
}
