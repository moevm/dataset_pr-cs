#include <stdio.h>
#include <stdlib.h>

int index_first_even(int arr[], int size);

int index_last_odd(int arr[], int size);

int sum_between_even_odd(int arr[], int size);

int sum_before_even_and_after_odd(int arr[], int size);

int main() {
    int keyInt;
    scanf("%d",&keyInt);
    int maxValue=1000;
    int arr[maxValue];
    int size = 0;
    while(getchar()!='\n'){
        scanf("%d",&arr[size]);
        size++;
    }

    switch (keyInt) {
        case 0:
            printf("%d\n", index_first_even(arr, size));
            break;
        case 1:
            printf("%d\n", index_last_odd(arr, size));
            break;
        case 2:
            printf("%d\n", sum_between_even_odd(arr, size));
            break;
        case 3:
             printf("%d\n", sum_before_even_and_after_odd(arr, size));
            break;
        default:
            printf("%s\n", "Данные некорректны");
    }
}

int sum_before_even_and_after_odd(int arr[], int size) {
    int sumOfElements=0;
    for (int i = 0; i < size; ++i) {
        if (i < index_first_even(arr, size) || i >= index_last_odd(arr, size)) {
            sumOfElements += abs(arr[i]);
        }
    }
    return sumOfElements;
}


int sum_between_even_odd(int arr[], int size) {
    int sumOfElements=0;
    for (int i = index_first_even(arr, size); i < index_last_odd(arr, size); ++i) {
        sumOfElements += abs(arr[i]);
    }
    return sumOfElements;
}

int index_last_odd(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        if (arr[size-i-1]%2!=0){
            return (size-i-1);
        }
    }
}

int index_first_even(int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        if (arr[i]%2==0){
            return i;
        }
    }
}

