#include <stdio.h>

int index_first_negative(int arr[], int len) {
    int i = 0;
    while (arr[i] >= 0 && i < len)
        i++;
    if (arr[i] < 0) {
        return i;
    } else
        return -1;
}

int index_last_negative(int arr[], int len) {
    int i = len - 1;
    while (arr[i] >= 0 && i >= 0)
        i--;
    if (arr[i] < 0) {
        return i;
    } else
        return -1;
}

int multi_between_negative(int arr[], int len) {
    int first_negative = index_first_negative(arr, len);
    int last_negative = index_last_negative(arr, len);
    int product = 1;
    for (int i = first_negative; i < last_negative; i++) {
        product *= arr[i];
    }
    return product;
}

int multi_before_and_after_negative(int arr[], int len) {
    int first_negative = index_first_negative(arr, len);
    int last_negative = index_last_negative(arr, len);
    int product = 1;
    for (int i = 0; i < first_negative; i++) {
        product *= arr[i];
    }
    for (int i = last_negative; i < len; i++) {
        product *= arr[i];
    }
    return product;
}

void output(int action, int arr[], int len) {
    switch (action) {
        case 0:
            if (index_first_negative(arr, len) == -1) {
                printf("Данные некорректны\n");
            } else
                printf("%d\n", index_first_negative(arr, len));
            break;
        case 1:
            if (index_last_negative(arr, len) == -1) {
                printf("Данные некорректны\n");
            } else
                printf("%d\n", index_last_negative(arr, len));
            break;
        case 2:
            if (index_first_negative(arr, len) == -1 || index_last_negative(arr, len) == -1) {
                printf("Данные некорректны\n");
            } else
                printf("%d\n", multi_between_negative(arr, len));
            break;
        case 3:
            if (index_first_negative(arr, len) == -1 || index_last_negative(arr, len) == -1) {
                printf("Данные некорректны\n");
            } else
                printf("%d\n", multi_before_and_after_negative(arr, len));
            break;
        default:
            printf("Данные некорректны\n");
    }
}

int main() {
    int action;
    int arr[20];
    int len = 0;
    scanf("%d", &action);
    do {
        scanf("%d", &arr[len]);
        len++;
    } while (getchar() != '\n');
    output(action, arr, len);
    return 0;
}