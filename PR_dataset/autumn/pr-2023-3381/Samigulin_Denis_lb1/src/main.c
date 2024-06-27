#include <stdio.h>
#include <stdlib.h>

int index_first_even(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] % 2 == 0) {
            return i;
        }
    }
    return -1;
}

int index_last_odd(int arr[], int n) {
    for (int i = n - 1; i >= 0; i--) {
        if (arr[i] % 2 != 0) {
            return i;
        }
    }
    return -1;
}

int sum_between_even_odd(int arr[], int first, int last) {
    int summa = 0;
    for (int i = first ; i < last; i++) {
        summa += abs(arr[i]);
    }
    return summa;
}

int sum_before_even_and_after_odd(int arr[], int first, int last, int n) {
    int summa_before = 0;
    int summa_after = 0;

    for (int i = 0; i < first; i++) {
        summa_before += abs(arr[i]);
    }

    for (int i = last; i < n; i++) {
        summa_after += abs(arr[i]);
    }

    return summa_before + summa_after;
}

int main() {
    int kase;
    scanf("%d", &kase);

    int arr[100];
    int n = 0;

    while (n < 100 && scanf("%d", &arr[n]) != EOF) {
        n++;
    }

    int first = index_first_even(arr, n);
    int last = index_last_odd(arr, n);

    if (last == -1 || first == -1 || first >= last) {
        printf("Данные некорректны\n");
        return 0;
    }

    switch (kase) {
        case 0:
            printf("%d\n", first);
            break;
        case 1:
            printf("%d\n", last);
            break;
        case 2:
            printf("%d\n", sum_between_even_odd(arr, first, last));
            break;
        case 3:
            printf("%d\n", sum_before_even_and_after_odd(arr, first, last, n));
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }

    return 0;
}
