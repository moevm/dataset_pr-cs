#include <stdio.h>
#include <stdlib.h>
int abs_max(int arr_int[], int count) {
    int max = -1;
    for (int i=0; i<count; i++) {
        if (abs(arr_int[i]) > abs(max)) {
            max = arr_int[i];
        }
    }
    return max;
}
int abs_min(int arr_int[], int count) {
    int min = 100000;
    for (int i=0; i<count; i++) {
        if (abs(arr_int[i]) < abs(min)) {
            min = arr_int[i];
        }
    }
    return min;
}
int diff(int arr_int[], int count) {
    int max = abs_max(arr_int, count);
    int min = abs_min(arr_int, count);
    return max-min;
}
int sum(int arr_int[], int count) {
    int sum = 0, index_max_el = 0;
    int max = abs_max(arr_int, count);
    for (int i=0; i<count; i++) {
        if (arr_int[i] == max) {
            index_max_el = i;
            break;
        }
    }
    for (int i=index_max_el; i<count; i++) {
        sum += arr_int[i];
    }
    return sum;
}

int main() {
    char symbol;
    int command, count = 0;
    int arr_int[100];
    scanf("%d%c", &command, &symbol);
    while (symbol == ' ') {
        scanf("%d%c", &arr_int[count], &symbol);
        count++;
    }
    switch (command) {
        case 0: printf("%d\n", abs_max(arr_int, count));
                break;
        case 1: printf("%d\n", abs_min(arr_int, count));
                break;
        case 2: printf("%d\n", diff(arr_int, count));
                break;
        case 3: printf("%d\n", sum(arr_int, count));
                break;
        default: printf("Данные некорректны\n");
    }
    return 0;
}