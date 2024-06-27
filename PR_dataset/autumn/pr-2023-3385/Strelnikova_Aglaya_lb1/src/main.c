#include <stdio.h> 
#include <stdlib.h>

int abs_max(int arr[], int len){
    int a = 0, max = 0;
    for(int i = 0; i < len; i++){
        if(abs(arr[i]) > max){
            max = abs(arr[i]);
            a = arr[i];
        }
    }   
    return a;
}

int abs_min(int arr[], int len){
    int a = arr[0];
    int min = abs(arr[0]);
    for(int i = 1; i < len; i++){
        if(abs(arr[i]) < min){
            min = abs(arr[i]);
            a = arr[i];
        }
    }
    return a;
}

int diff(int arr[], int len){
    return abs_max(arr, len) - abs_min(arr, len);
}

int sum(int arr[], int len){
    int x = abs_max(arr, len);
    int sum = 0, f = 0;
    for(int i = 0; i < len; i++){
        if (f == 0 && arr[i] == x){
            f = 1;
        }
        if (f == 1){
            sum += arr[i];
        }
    }
    return sum;
}

int main(){
    int n = 0, N = 100;
    int task, arr[N];
    scanf("%d", &task);
    char c;
    do{
        scanf("%d%c", &arr[n], &c);
        n++;
    } while (n < N && c != '\n');
    int len = n;
    switch (task){
    case 0:
        printf("%d\n", abs_max(arr, len));
        break;
    case 1:
        printf("%d\n", abs_min(arr, len));
        break;
    case 2:
        printf("%d\n", diff(arr, len));
        break;
    case 3:
        printf("%d\n", sum(arr, len));
        break;
    default:
        puts("Данные некорректны\n");
    }
    return 0;
}

