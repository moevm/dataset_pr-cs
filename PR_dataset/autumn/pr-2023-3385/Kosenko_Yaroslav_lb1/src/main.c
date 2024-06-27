#include <stdio.h>
#include <stdlib.h>

#define N 100

int index_first_negative(int arr[N], int n){
    for (int i = 0; i < n; i++){
        if (arr[i] < 0) return i;
    }
}

int index_last_negative(int arr[N], int n){
    for (int i = n-1; i >= 0; i--){
        if (arr[i] < 0) return i;
    }
}

long long int sum_between_negative(int arr[N], int n){
    int begin = index_first_negative(arr, n);
    int end = index_last_negative(arr, n);
    long long int sum = 0;
    for (int i = begin; i < end; i++){
        sum += abs(arr[i]);
    }
    return sum;
}

long long int sum_before_and_after_negative(int arr[N], int n){
    int begin = index_last_negative(arr, n);
    int end = index_first_negative(arr, n);
    long long int sum = 0;
    for (int i = 0; i < end; i++){
        sum += abs(arr[i]);
    }
    for (int i = begin; i < n; i++){
        sum += abs(arr[i]);
    }
    return sum;
}

int main(){
    int arr[N];
    int mode;
    int n = 0;
    char c;
    scanf("%d%c",&mode, &c);
    do{
        scanf("%d%c", &arr[n], &c);
        n++;
    } while (c != '\n');
    switch (mode){
        case 0:
            printf("%d\n", index_first_negative(arr, n));
            break;
        case 1:
            printf("%d\n", index_last_negative(arr, n));
            break;
        case 2:
            printf("%lld\n", sum_between_negative(arr, n));
            break;
        case 3:
            printf("%lld\n", sum_before_and_after_negative(arr, n));
            break;
        default:
            printf("Данные некорректны");
    }
}
