#include <stdio.h>
#include <stdlib.h>

int abs_max(int arr[], int size){
    int max = 0;
    for( int i = 0 ; i < size ; i++){
        if (abs(arr[i]) > abs(max)){
            max = arr[i];
        }
    }
    return max;
}

int index_1(int arr[], int size){
    int index_max = 0;
    int max = 0;
    for( int i = 0 ; i < size ; i++){
        if (abs(arr[i]) > abs(max)){
            index_max = i;
            max = arr[i]; 
        }
    }
    return index_max;
}
    
int abs_min(int arr[], int size){
    int min = 100;
    for( int i=0 ; i < size; i++ ){
        if (abs(arr[i]) < abs(min)){
            min = arr[i];
        }
    }
    return min;
}

int diff(int arr[] , int size){
    int dif = abs_max(arr, size) - abs_min(arr, size);
    return dif;
}

int sum(int arr[] , int size){
    int sam = 0;
    int index_m = index_1(arr, size);
    for( int i = index_m; i<size; i++){
        sam +=arr[i];
    }
    return sam;
}

int main(){
    int arr[100];
    int a;
    char space;
    int size = 0;
    scanf( "%d%c", &a , &space );
    for( int i = 0 ; i < 100 ; i++ ){
        scanf( "%d%c", &arr[i] , &space );
        size++;
        if (space == '\n'){
            break;
        }
    }
    int b;
    switch(a){
        case 0:
            b = abs_max(arr, size);
            printf("%d\n", b);
            break;
        case 1:
            b = abs_min(arr, size);
            printf("%d\n", b);
            break;
        case 2:
            b = diff(arr, size);
            printf("%d\n", b);
            break;
        case 3:
            b = sum(arr, size);
            printf("%d\n", b);
            break;
        default:
        printf("Данные некорректны\n");
    }
    return 0;
}