#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"

int main() {
    int command, count = 0; //значение 0123, счетчик элементов
    int mas[100]; //Массив для записи целых чисел
    scanf("%d", &command); //ввод значения 0123
    char ch; //переменная для пробела или \n
    for (int ind = 0; (ch = getchar()) != '\n'; ind++) {
        scanf("%d", &mas[ind]);
        count++;
    }
    switch (command) {
        case 0:
            printf("%d\n", index_first_even(mas, count));
            break;
        case 1:
            printf("%d\n", index_last_odd(mas, count));
            break;
        case 2:
            printf("%d\n", sum_between_even_odd(mas, count));
            break;
        case 3:
            printf("%d\n", sum_before_even_and_after_odd(mas, count));
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
    return 0;
}
