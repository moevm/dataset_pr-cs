#include <stdio.h>
#include <locale.h>

int index_first_negative(int arr[], int amount) {

    int first_negative = 0;
    int number = -1;

    for (int i = 0; i < amount; i++) {
        if (arr[i] < 0) {
            first_negative = arr[i];
            number = i;
            break;
        }
    }

    return number;
}

int index_last_negative(int arr[], int amount) {

    int last_negative = 0;
    int number = 0;

    for (int i = 0; i < amount; i++) {
        if (arr[i] < 0) {
            last_negative = arr[i];
            number = i;
        }
    }

    return number;
}

int multi_between_negative(int arr[], int amount) {

    int number_first_negative = index_first_negative(arr, amount);
    int number_last_negative = index_last_negative(arr, amount);
    int multi = 1;

    for (int i = number_first_negative; i < number_last_negative; i++) {
        multi *= arr[i];
    }
    return multi;
}

int multi_before_and_after_negative(int arr[], int amount) {

    int number_first_negative = index_first_negative(arr, amount);
    int number_last_negative = index_last_negative(arr, amount);
    int multi = 1;

    for (int i = 0; i < number_first_negative; i++) {
        multi *= arr[i];
    }
    for (int i = number_last_negative; i < amount; i++) {
        multi *= arr[i];
    }

    return multi;
}

int main() {
    setlocale(LC_ALL, "rus");

    int N, arr[21];
    char c = ' ';
    int amount = 0;
    int answer;

    scanf("%d", &N);
    while (c != '\n') {

        scanf("%d%c", &arr[amount], &c);
        amount += 1;
    } 
    if (N != 0 && N != 1 && N != 2 && N != 3) {
        printf("Данные некорректны");
        return 0;
    }

    switch (N) {
    case 0: 
        answer = index_first_negative(arr, amount);
        break;
    case 1: 
        answer = index_last_negative(arr, amount);
        break;
    case 2:
        answer = multi_between_negative(arr, amount);
        break;
    case 3:
        answer = multi_before_and_after_negative(arr, amount);
        break;   
    }
    
    printf("%d", answer);
}
