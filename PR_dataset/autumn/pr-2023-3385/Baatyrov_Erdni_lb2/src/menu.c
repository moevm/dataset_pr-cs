#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"


int main() {
    int n = 0;
    int N = 20;
    int arr[N];
    char c;
    int choice;
    scanf("%d%c", &choice, &c);
    do {
        scanf("%d%c", &arr[n], &c);
        n++;
    }while(c!=  '\n' && n < N);
    int answer;
    switch (choice) {
    case 0:
        answer = index_first_negative(arr, n);
        printf("%d\n", answer);
        return 0;
        break;
    case 1:
        answer = index_last_negative(arr, n);
        printf("%d\n", answer);
        return 0;
        break;
    case 2:
        multi_between_negative(arr, n);
        return 0;
        break;
    case 3:
        multi_before_and_after_negative(arr, n);
        return 0;
        break;
    }
    printf("Данные некорректны\n");
    return 0;
}
