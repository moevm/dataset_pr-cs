#include <stdio.h>
#include <stdlib.h>

int index_first_even(int arr[100], int arr_length){
    int index = -1;
    for (int i = 0; i <= arr_length; i++){
        if (abs(arr[i] % 2) == 0){
            index = i;
            break;
        }
    }
    return index;
}
int index_last_odd(int arr[100], int arr_length){
    int index = -1;
    for (int i = arr_length-1; i >= 0; i--){
        if (abs(arr[i]) % 2 == 1){
            index = i;
            break;
        }
    }
    return index;
}

int sum_between_even_odd(int arr[100], int arr_length){
    int sum = 0;
    for (int i = index_first_even(arr, arr_length); i < index_last_odd(arr, arr_length); i++){
        sum += abs(arr[i]);
    }
    return sum;
}

int sum_before_even_and_after_odd(int arr[100], int arr_length){
    int sum = 0;

    for (int i = 0; i < index_first_even(arr, arr_length); i++){
        sum += abs(arr[i]);
    }
    for (int i = index_last_odd(arr, arr_length); i < arr_length; i++){
        sum += abs(arr[i]);
    }
    return sum;
}

int main() {
    int func_value;
    int arr[100];
    int index = 0;

    scanf("%d", &func_value);

    while (getchar() != '\n'){
        scanf("%d", &arr[index]);
        index+=1;
    }

    switch (func_value){
        case 0:
            printf("%d", index_first_even(arr, index));
            break;
        case 1:
            printf("%d", index_last_odd(arr, index));
            break;
        case 2:
            printf("%d", sum_between_even_odd(arr, index));
            break;
        case 3:
            printf("%d", sum_before_even_and_after_odd(arr, index));
            break;
        default:
            printf("Данные некорректны");
    }

    return 0;
}