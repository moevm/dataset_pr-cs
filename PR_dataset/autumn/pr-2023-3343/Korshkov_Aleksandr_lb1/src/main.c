#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

int index_first_negative(int arr[20], int m) {
    for (int i = 0; i < 20; i++) {
        if (arr[i] < 0) {
            if (m == 1) {
                printf("%d", i);
            }
            return i; 
        }
    }

    printf("Данные некорректны");
    exit(0);
}

int index_last_negative(int arr[20], int m) { 
    int last_index = -1; 
    for (int i = 0; i < 20; i++) {
        if (arr[i] < 0) {
            last_index = i;
        }
    }

    if (last_index != -1) {
        if (m == 1) {
            printf("%d", last_index);
        }
        return last_index;
    }
    else {
        printf("Данные некорректны");
        exit(0);
    }
    
}

void multi_between_negative(int arr[20]) {
    int k = 1, start = index_first_negative(arr, 0), 
    finish = index_last_negative(arr, 0);

    for (start;start < finish;start++) {
        k *= arr[start];
    }

    printf("%d", k);
}

void multi_before_and_after_negative(int arr[20], int finish2) {
    int k = 1, finish1 = index_first_negative(arr, 0), 
    start2 = index_last_negative(arr, 0);

    for (int start = 0; start < finish1; start++) {
        k *= arr[start];
    }
    for (start2; start2 < finish2; start2++) {
        k *= arr[start2];
    }

    printf("%d", k);
}


int main() {
    setlocale(LC_ALL, "Rus");

    int arr[20], n, i = 0;
    for (i; i < 20; i++) {
        arr[i] = 0;
    }

    i = 0;
    scanf("%d", &n); 
    do {
        scanf("%d", &arr[i]); 
        i++;
    }
    while (getchar() != '\n');

    switch (n) {
    case 0:
        index_first_negative(arr, 1);
        break;
    case 1:
        index_last_negative(arr, 1);
        break;
    case 2:
        multi_between_negative(arr);
        break;
    case 3:
        multi_before_and_after_negative(arr, i);
        break;
    default:
        printf("Данные некорректны");
        break;
    }

    return 0;
}
