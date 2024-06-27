#include <stdio.h>

int index_first_negative (int arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0)
            return i;
    }
}

int index_last_negative (int arr[], int size) {
    for (int i = size-1; i > -1; i--) {
        if (arr[i] < 0)
            return i;
    }
}

int multi_between_negative (int arr[], int size) {
    int multi = 1;
    for (int i = index_first_negative(arr, size); i < index_last_negative(arr, size); i++)
        multi *= arr[i];
    return multi;
}

int multi_before_and_after_negative (int arr[], int size) {
    int multi = 1;

    for (int i = 0; i < index_first_negative(arr, size); i++)
        multi *= arr[i];

    for (int i = index_last_negative(arr, size); i < size; i++)
        multi *= arr[i];

    return multi;
}

int array_processing (int option, int arr[], int size) {
    switch (option) {
        case 0:
            printf("%d\n", index_first_negative(arr, size));
            break;
        case 1:
            printf("%d\n", index_last_negative(arr, size));
            break;
        case 2:
            printf("%d\n", multi_between_negative(arr, size));
            break;
        case 3:
            printf("%d\n", multi_before_and_after_negative(arr, size));
            break;
        default:
            printf("%s\n", "Данные некорректны");
    }

    return 0;
}

int main() {
    int option;
    int numbers[20];

    int size = 0;
    scanf("%d", &option);

    while (getchar() != '\n') {
        scanf("%d", &numbers[size]);
        size++;
    }

    array_processing(option, numbers, size);
    return 0;
}