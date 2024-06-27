#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int cmp(void *a, void*b){
    const int *f= (const int *) a;
    const int *s= (const int *) b;
    if (*f>*s)
        return 1;
    
    if (*f<*s)
        return -1;
    
    return 0;
}
int main(){
    int arr[1000];
    for (int i=0; i<1000; i++){
        int a;
        scanf("%d", &a);
        arr[i]=a;
    }
    double time_1=0.0;
    clock_t begin_1 =clock();
    bubbleSort(arr, 100);
    clock_t end_1 =clock();
    time_1 += (double)(end_1 - begin_1) / CLOCKS_PER_SEC;


    double time_2=0.0;
    clock_t begin_2 =clock();
    qsort(arr, 1000, sizeof(int), cmp);
    clock_t end_2 =clock();
    time_2 += (double)(end_2 - begin_2) / CLOCKS_PER_SEC;
    for (int i =0 ; i<999; i++){
        printf("%d ", arr[i]);
    }
    printf("%d\n", arr[999]);
    printf("%lf\n", time_1);
    printf("%lf", time_2);
    return 0;
}
