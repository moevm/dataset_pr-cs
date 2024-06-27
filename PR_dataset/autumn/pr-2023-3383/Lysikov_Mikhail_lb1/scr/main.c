#include <stdio.h>
#include <stdlib.h>
int abs_max(int arr[], int size) {
    int max = 1;
    for (int i = 0; i < size; i++) {
        if (abs(arr[i]) > abs(max)) {
            max = arr[i];
        }
    }
return max;
}

int abs_min(int arr[], int size) {
    int min = 1001;
    for (int i = 0; i < size; i++) {
        if (abs(arr[i]) < abs(min)) {
            min = arr[i];
        }
     }
return min;
}

int diff(int arr[], int size) {
    return abs_max(arr, size) - abs_min(arr, size);
}

int sum(int arr[], int size) {
 int sum = 0, flag = 0;
 int max = abs_max(arr, size);
 for (int i=0; i<size; i++) {
     if (flag && size < 101){
         sum+= arr[i-1];
     }
     if (arr[i]==max){
         flag = 1;
     }
 }sum = sum + arr[size-1];
 return sum;
}

int main(){
    int arr[100],size = 0, flag =1, option;
    char space;
    scanf("%d%c", &option, &space);
    while (flag){
        scanf("%d%c", &arr[size], &space);
        size++;
        if (space != ' ' ){
            flag = 0;
        }
    }
    switch (option) {
     case 0: printf("%d\n", abs_max(arr, size));break;
     case 1: printf("%d\n", abs_min(arr, size));break;
     case 2: printf("%d\n", diff(arr, size));break;
     case 3: printf("%d\n", sum(arr, size));break;
     default: printf("Данные некорректны\n");
 }
 return 0;
}