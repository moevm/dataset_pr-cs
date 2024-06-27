#include <stdio.h>
#include <stdlib.h>
#define N 100 //размер массива

int n;
int arr[N];

int index_first_zero(int arr[], int size){
    for(int i=0; i<size; i++){ //начало-конец
        if(arr[i] == 0){
            return i;
        }
    }
    return -1; //в случае ошибки
}
int index_last_zero(int arr[], int size){
    for(int i=size-1; i>=0; i--){ //конец-начало
        if(arr[i]==0){
            return i;
        }
    }
    return -1;
}
int sum_between(int arr[], int size){
    int first=index_first_zero(arr, size);
    int last=index_last_zero(arr, size);
    int sum=0;
    for(int i=first+1; i<last;i++){ //от нуля до нуля
        sum+=abs(arr[i]);
    }
    return sum;
}
int sum_before_and_after(int arr[], int size){
    int first=index_first_zero(arr, size);
    int last=index_last_zero(arr, size);
    int sum=0;
    for(int i=0;i<first; i++){
        sum+=abs(arr[i]);
    }
    for(int i=last+1; i<size; i++){
        sum+=abs(arr[i]);
    }
    return sum;
}
//хлеб
int main(){
    scanf("%d", &n);
    
    int counter=0;
    while(counter<N){
        scanf("%d", &arr[counter]);
        counter++;
        if(getchar()=='\n'){
            break;
        }
    }
    switch(n){
        case 0:
        printf("%d\n", index_first_zero(arr, counter));
        break;
        
        case 1:
        printf("%d\n", index_last_zero(arr, counter));
        break;
        
        case 2:
        printf("%d\n", sum_between(arr, counter));
        break;
        
        case 3:
        printf("%d\n", sum_before_and_after(arr, counter));
        break;
        
        default:
        printf("Данные некорректны\n"); //число не 0,1,2,3
        break;
    }
    return 0;
}
