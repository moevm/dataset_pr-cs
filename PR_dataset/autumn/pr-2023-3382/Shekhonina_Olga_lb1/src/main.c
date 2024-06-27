#include <stdio.h>
#include <stdlib.h>

int index_first_negative(int arr[], int size){
    int ind;
    for (int i = 0;i<size;i++){
        if (arr[i]<0){
            ind = i;
            break;
        }
    }
    return ind;
}

int index_last_negative(int arr[], int size){
    int ind;
    for (int i = size - 1;i>=0;i--){
        if (arr[i]<0){
            ind = i;
            break;
        }
    }
    return ind;
}

int sum_between_negative(int arr[], int size){
    int ind1 = index_first_negative(arr, size);
    int ind2 = index_last_negative(arr, size);
    int sum = 0;
    for (int i = ind1; i<ind2; i++){
        sum+=abs(arr[i]);
    }
    return sum;
}

int sum_before_and_after_negative(int arr[], int size){
    int sumall = 0;
    int sum1 = sum_between_negative(arr, size);
    int sum = 0;
    for (int i = 0; i<size; i++){
        sumall+=abs(arr[i]);
    }
    sum = sumall - sum1;
    return sum;
}

int main()
{   int arr[100];
    int size = 0;
    int number = 0;
    scanf ("%d",  &number);
    char c;
    while (c!='\n'){
        scanf("%d%c", &arr[size], &c);
        size++;
    }
    switch(number){
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