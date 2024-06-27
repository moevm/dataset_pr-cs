#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 100

int index_first_negative(int arr[], int size){
    for(int i=0;i<size;i++){
        if(arr[i]<0){
            return i;
            break;
        }
    }
}

int index_last_negative(int arr[], int size){
    for(int i=size-1;i>=0;i--){
        if(arr[i]<0){
            return i;
            break;
        }
    }
}

int sum_between_negative(int arr[], int size){
    //сумма модулей эл. массива (от 1-го отриц. (вкл. эл.) и до послед. отриц. (не вкл. эл.))
    int index_first = index_first_negative(arr, size);
    int index_last = index_last_negative(arr, size);
    int summ = 0;
    for(int i = index_first; i < index_last; i++){
        summ += abs(arr[i]);
    }
    return summ;
}

int sum_before_and_after_negative(int arr[], int size){
    //сумма модулей эл. массива (до 1-го отриц. (не вкл. эл.) и после послед. отриц. (вкл. эл.))
    int index_first = index_first_negative(arr, size);
    int index_last = index_last_negative(arr, size);
    int summ = 0;
    for(int i=0; i < index_first; i++){
        summ += abs(arr[i]);
    }
    for(int i = index_last; i<size; i++){
        summ += abs(arr[i]);
    }
    return summ;
}

int main(){

    //Ввод данных ...
    int key_value;
    scanf("%d", &key_value);

    int size = 0;
    int arr[MAX_LEN];
    while(getchar()!='\n'){
        scanf("%d", &arr[size]);
        size++;
    }
    //...

    switch(key_value){

        case 0:
            printf("%d\n", index_first_negative(arr, size));
            break;

        case 1:
            printf("%d\n", index_last_negative(arr, size));
            break;

        case 2:
            printf("%d\n", sum_between_negative(arr, size));
            break;

        case 3:
            printf("%d\n", sum_before_and_after_negative(arr, size));
            break;

        default:
            printf("Данные некорректны");
    }
    return 0;
}
