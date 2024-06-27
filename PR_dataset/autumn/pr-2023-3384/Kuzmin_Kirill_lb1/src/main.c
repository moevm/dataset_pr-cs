#include <stdio.h>            // подключаем заголовочный файл stdio.h
#define N 20


//0 : индекс первого отрицательного элемента. (index_first_negative)
//1 : индекс последнего отрицательного элемента. (index_last_negative)
//2 : (multi_between_negative)
//3 : (multi_before_and_after_negative)int main() {
int index_first_negative(int arr[], int n) {
    int ind = -1;
    for (int i = 0; i < n; i++){
        if (arr[i] < 0) {
            ind = i;
            break;
        }
    }
    return ind;
}

int index_last_negative(int arr[], int n) {
    int ind = -1;
    for (int i = n-1; i > 0; i--){
        if (arr[i] < 0) {
            ind = i;
            break;
        }
    }
    return ind;
}

int multi_between_negative(int arr[], int n) {
    int milty = 1;
    int first = index_first_negative(arr, n);
    int last = index_last_negative(arr, n);
    for (int i = first; i < last; i++) {
        milty *= arr[i];
    }
    return milty;
}
int multi_before_and_after_negative(int arr[], int n) {
    int milty = 1;
    int first = index_first_negative(arr, n);
    int last = index_last_negative(arr, n);
    for (int i = 0; i < first; i++) {
        milty *= arr[i];
    }
    for (int i = last; i < n; i++) {
        milty *= arr[i];
    }
    return milty;
}
int main() {
    int n = 0;
    int arr[N];
    char c;
    int choice;
    scanf("%d%c", &choice, &c);
    do {
        scanf("%d%c", &arr[n], &c);
        n++;
    } while (c != '\n' && n < N);
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
            answer = multi_between_negative(arr, n);
            printf("%d\n", answer);
            return 0;
            break;
        case 3:
            answer = multi_before_and_after_negative(arr, n);
            printf("%d\n", answer);
            return 0;
            break;
        default:
            printf("Данные некорректны\n");
    }
    return 0;
}