#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int index_first_negative(int arr[], size_t size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            return i;
        }
    }
    return -1; 
}

int index_last_negative(int arr[], size_t size) {
    for (int i = size - 1; i >= 0; i--) {
        if (arr[i] < 0) {
            return i;
        }
    }
    return -1; 
}

int multi_between_negative(int arr[], size_t size) {
    size_t start = index_first_negative(arr, size);
    size_t end = index_last_negative(arr, size);
    if (start == -1 || end == -1) {
        return 0; 
    }

    int result = 1;
    for (int i = start; i < end; i++) {
        result *= arr[i];
    }
    return result;
}

int multi_before_and_after_negative(int arr[], size_t size) {
    size_t start = index_first_negative(arr, size);
    size_t end = index_last_negative(arr, size);
    if (start == -1 || end == -1) {
        return 0; 
    }

    int result = 1;
    for (int i = 0; i < start; i++) {
        result *= arr[i];
    }
    for (int i = end; i < size; i++) {
        result *= arr[i];
    }

    return result;
}

int main()
{
    int choice;
    scanf("%d", &choice);

    char input[500]; 
    fgets(input, sizeof(input), stdin);

    int arr[20];
    size_t size = 0;

    char *token = strtok(input, " \n"); 

    while (token != NULL) {
        arr[size] = atoi(token);
        size++;
        token = strtok(NULL, " \n");
    }
    
    switch (choice) {
        case 0:
            printf("%d\n", index_first_negative(arr, size));
            break;
        case 1:
            printf("%d\n", index_last_negative(arr, size));
            break;
        case 2: {
            printf("%d\n", multi_between_negative(arr, size));
            break;
        }
        case 3: {
            printf("%d\n", multi_before_and_after_negative(arr, size));
            break;
        }
        default:
            printf("Данные некорректны\n");
    }
    
    return 0;
}
