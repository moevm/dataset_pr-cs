#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_before_and_after_negative.h"
#include "sum_between_negative.h"
#include <stdio.h>

#define ANSWER 0
#define N 100

void input(int arr[], int *n) {
    int key;
    char c;

    scanf("%d%c", &key, &c);
    while (c != '\n' && *n < N) {
        scanf("%d%c", &arr[*n], &c);
        (*n)++;
    }
}

int menu(int arr[], int n, int key) {
    int answer = 0;

    switch (key) {
    case 0:
        answer = index_first_negative(arr, n);
        break;
    case 1:
        answer = index_last_negative(arr, n);
        break;
    case 2:
        answer = sum_between_negative(arr, n);
        break;
    case 3:
        answer = sum_before_and_after_negative(arr, n);
        break;
    default:
        puts("Данные некорректны");
        return 0;
    }

    return answer;
}

int main(void) {
    int arr[N]; // 0 .. N-1
    int n = 0;

    input(arr, &n);

    int key;
    scanf("%d", &key);

    int answer = menu(arr, n, key);

    printf("%d\n", answer);

    return 0;
}
