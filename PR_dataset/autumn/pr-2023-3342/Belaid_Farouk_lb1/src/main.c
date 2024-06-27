#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int index_first_zero(int arr[], int size) {
    int index;
    for (int i = 0; i < size; i++) {
        if (arr[i] == 0) {
            index = i;
            break;
        }
    }
    return index;
}

int index_last_zero(int arr[], int size) {
     int index;
    for (int i = size - 1; i >= 0; i--) {
        if (arr[i] == 0) {
            index = i;
            break;
        }
    }
    return index;
}


int sum_between(int arr[], int size) {
    int first_zero_index = index_first_zero(arr, size);
    int last_zero_index = index_last_zero(arr, size);
    
    
    int sum = 0;
    for (int i = first_zero_index + 1; i < last_zero_index; i++) {
        sum += abs(arr[i]);
    }
    return sum;
}

int sum_before_and_after(int arr[], int size) {
    int first_zero_index = index_first_zero(arr, size);
    int last_zero_index = index_last_zero(arr, size);

    int sum_before = 0;
    for (int i = 0; i < first_zero_index; i++) {
        sum_before += abs(arr[i]);
    }
    
    int sum_after = 0;
    for (int i = last_zero_index + 1; i < size; i++) {
        sum_after += abs(arr[i]);
    }
    
    return sum_before + sum_after;
}

int main() {
    char input[1024];
    
    fgets(input, sizeof(input), stdin);
    char *token = strtok(input, " \n");
    
    if (token == NULL) {
        printf("Данные некорректны\n");
        return 1;
    }
    
    int choice = atoi(token);
    int arr[100];
    int size = 0;
    
    token = strtok(NULL, " \n");
    
    while (token != NULL && size < 100) {
        arr[size++] = atoi(token);
        token = strtok(NULL, " \n");
    }
    
    // Обработка выбора
    switch (choice) {
        case 0:
            printf("%d\n", index_first_zero(arr, size));
            break;
        case 1:
            printf("%d\n", index_last_zero(arr, size));
            break;
        case 2:
            printf("%d\n", sum_between(arr, size));
            break;
        case 3:
            printf("%d\n", sum_before_and_after(arr, size));
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
    
    return 0;
}