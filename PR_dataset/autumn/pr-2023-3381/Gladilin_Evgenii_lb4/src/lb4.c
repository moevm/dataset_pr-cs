#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const void *a, const void *b){
    const int *f = (const int*) a;
    const int *s = (const int*) b;
    if(*f>*s)
        return 1;
    if(*f<*s)
        return -1;
    return 0;
}

void bubble_sort(int* arr,int size){
    for(int i = 0;i<size;i++){
        for(int j = 0; j<size-i-1;j++){
            int temp = 0;
            if(arr[j] > arr[j+1]){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
	    }
        }
    }
}

int main(){
    int arr1[1000];
    int arr2[1000];
    double start,end;
    for(int i = 0;i<1000;i++){
        scanf("%d",&arr1[i]);
        arr2[i] = arr1[i];
    }

    start = clock();
    qsort(arr1,sizeof(arr1)/sizeof(int),sizeof(int),cmp);
    end = clock();
    double qsort_time = end - start;

    start = clock();
    bubble_sort(arr2,sizeof(arr2)/sizeof(int));
    end = clock();
    double bubble_time = end - start;

    for(int i = 0; i<sizeof(arr2)/sizeof(int);i++){
        printf("%d ", arr2[i]);
    }
    printf("\n%f\n%f", bubble_time, qsort_time);
    return 0;
}
