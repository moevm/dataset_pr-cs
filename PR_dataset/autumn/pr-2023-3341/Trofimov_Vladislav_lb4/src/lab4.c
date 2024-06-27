#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LENGTH 1000

int cmp(const void *first,const void *second){
    if (abs((*(int*)first)) < abs((*(int*)second))) return 1;
    if (abs((*(int*)first)) > abs((*(int*)second))) return -1;
    return 0;
}

void input_arr(int arr[]){
    for (int i = 0; i < LENGTH;i++){
        scanf("%d", &arr[i]);
    }
}

void output_arr(int arr[], int time_qsort){
    for (int i = 0; i < LENGTH; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("%d", time_qsort);
}

int main(){
    int arr[LENGTH];
    input_arr(arr);
    time_t time_qsort = time(NULL);
    qsort(arr,sizeof(arr)/sizeof(int),sizeof(int),cmp);
    time_qsort = time(NULL) - time_qsort;
    output_arr(arr,time_qsort);
    return 0;
}
