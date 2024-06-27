#include <stdio.h>
#define N 20

int index_first_negative(int arr[], int size) {
    int answer;
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            answer = i;
            break;
        }
    }
    return answer;
}

int index_last_negative(int arr[], int size) {
    int answer;
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            answer = i;
        }
    }
    return answer;
}

int multi_between_negative(int arr[], int size) {
    int i1 = 100000, i2, answer = 1;
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            if (i1 == 100000) {
                i1 = i;
            } else {
                i2 = i;
            }
        }
    }
    for (int i = i1; i < i2; i++) {
        answer *= arr[i];
    }
    return answer;
}

int multi_before_and_after_negative(int arr[], int size) {
    int i1 = 100000, i2, answer = 1;
    for (int i = 0; i < size; i++) {
        if (arr[i] < 0) {
            if (i1 == 100000) {
                i1 = i;
            } else {
                i2 = i;
            }
        }
    }
    for (int i = 0; i < i1; i++) {
        answer *= arr[i];
    }
    for (int i = i2; i < size; i++) {
        answer *= arr[i];
    }
    return answer;
}

int main() {
    int n, size = 0;
    char c;
    int arr[N];
    scanf("%d", &n);
    c = getchar();
    for (int i = 0; i < N; i++) {
        if (c == '\n') {
            break;
        } else {
            scanf("%d", &arr[i]);
            c = getchar();
            size++;
        }
    }
    switch (n) {
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
            printf("Данные некорректны\n");
        }
    return 0;
}
