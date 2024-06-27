#include <stdio.h>
#include <stdlib.h>
#define ARRAY_LENDTH 100
#define ERROR_MESSAGE "Данные некорректны"

int index_first_even(int arr[], int size){
    for (int i=0; i<size; i++)
        if (arr[i]%2==0)
            return i;
}
int index_last_odd(int arr[], int size){
    for (int i = size - 1; i >= 0; i--)
        if (arr[i] % 2 != 0)
            return i;
}
int sum_between_even_odd(int arr[], int size){
    int sum = 0;
    for (int i = index_first_even(arr, size); i < index_last_odd(arr, size); ++i){
        sum += abs(arr[i]);
    }
    return sum;
}
int sum_before_even_and_after_odd(int arr[], int size) {
    int sum = 0;
    for (int i = 0; i < index_first_even(arr, size); ++i)
        sum += abs(arr[i]);
    for (int j = index_last_odd(arr, size); j < size; ++j)
        sum += abs(arr[j]);
    return sum;
}
int main(){
    int size = 0;
    char symbol;
    int arr[ARRAY_LENDTH];
    int type;
    scanf("%d", &type);

    while(symbol!='\n')
    {
        scanf("%d%c", &arr[size], &symbol);
        size++;
    }
switch (type){
    case 0:
        printf("%d", index_first_even(arr,size));
        break;
    case 1:
        printf("%d", index_last_odd(arr,size));
        break;
    case 2:
        printf("%d", sum_between_even_odd(arr,size));
        break;
    case 3:
        printf("%d", sum_before_even_and_after_odd(arr,size));
        break;
    default:
        printf("%s\n", ERROR_MESSAGE);
        break;
    }
    return 0;
}