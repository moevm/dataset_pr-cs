#include <stdio.h>
#include <stdlib.h>

int index_first_even(int mas[], int count) {
    for (int ind = 0; ind < count; ind++) {
        if (mas[ind] % 2 == 0) {
            return ind;
        }
    }
}

int index_last_odd(int mas[], int count) {
    for (int ind = count - 1; ind >= 0; ind--) {
        if (abs(mas[ind] % 2) == 1) {
            return ind;
        }
    }
}

int sum_between_even_odd(int mas[], int first_even, int last_odd) {
    int sm = 0;
    for (int ind = first_even; ind < last_odd; ind++) {
        sm += abs(mas[ind]);
    }
    return sm;
}

int sum_before_even_and_after_odd(int mas[], int count, int first_even, int last_odd) {
    int sm = 0;
    for (int ind = 0; ind < first_even; ind++) {
        sm += abs(mas[ind]);
    }
    for (int ind = last_odd; ind < count; ind++) {
        sm += abs(mas[ind]);
    }
    return sm;
}

int main() {
    int command, count = 0; //значение 0123, счетчик элементов
    int mas[100]; //Массив для записи целых чисел
    scanf("%d", &command); //ввод значения 0123
    char ch; //переменная для пробела или \n
    for (int ind = 0; (ch = getchar()) != '\n'; ind++) {
        scanf("%d", &mas[ind]);
        count++;
    }
    int first_even = index_first_even(mas, count);
    int last_odd = index_last_odd(mas, count);
    switch (command) {
        case 0:
            printf("%d\n", index_first_even(mas, count));
            break;
        case 1:
            printf("%d\n", index_last_odd(mas, count));
            break;
        case 2:
            printf("%d\n", sum_between_even_odd(mas, first_even, last_odd));
            break;
        case 3:
            printf("%d\n", sum_before_even_and_after_odd(mas, count, first_even, last_odd));
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
    return 0;
}