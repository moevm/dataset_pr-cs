#include <stdio.h>
#define N  100

int max_numbers(int arr[], int size)
{
    int max = arr[0];
    for (int i = 0; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

int min_numbers(int arr[], int size) {
    int min = arr[0];
    for (int i = 0; i < size; i++) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

int diff_numbers(int max,int min) {
    return max - min;
}

int sum_numbers(int arr[], int size, int min) {
    int sum = 0; int i = 0;
    while (arr[i] != min) {
        sum += arr[i];
        i++;
    }
    return sum;
}



int main() {
    int mas[N];
    int item; int max_el, min_el,diff_el,sum_el;
    char symbol,symbol_item;
    int count_el = 0;

    scanf("%d%c", &item, &symbol_item);
    if (symbol_item == '\n') {
        printf("Данные некорректны");
        return 0;
    }

    for (int i = 0; i < N; i++)
    {
        scanf("%d%c", &mas[i], &symbol); 
        count_el++;
        if (symbol == '\n') {  
            break;
        }
    }
    switch (item) {
    case 0:
        max_el = max_numbers(mas, count_el);
        printf("%d\n", max_el);
        break;
    case 1:
        min_el = min_numbers(mas, count_el);
        printf("%d\n", min_el);
        break;
    case 2:
        diff_el = diff_numbers(max_numbers(mas, count_el), min_numbers(mas, count_el));
        printf("%d\n", diff_el);
        break;
    case 3:
        sum_el = sum_numbers(mas, count_el, min_numbers(mas, count_el));
        printf("%d\n", sum_el);
        break;
    default:
        printf("Данные некорректны\n");
        return 0;
    }
    return 0;
}