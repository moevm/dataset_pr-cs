#include <stdio.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"

int main() {

    // Инициализация флага
    int flag;
    scanf("%d ", &flag);

    // Инициализация массива
    int array[100];
    char end_cur_value;
    int count = 0;
    do {
        scanf("%d%c", &array[count], &end_cur_value);
        ++count;
    } while (end_cur_value != '\n');

    // Обработка данных
    switch (flag) {
    case 0:
        printf("%d\n", index_first_even(array));
        return 0;
    case 1:
        printf("%d\n", index_last_odd(array, count));
        return 0;
    case 2:
        printf("%d\n", sum_between_even_odd(array, count));
        return 0;
    case 3:
        printf("%d\n", sum_before_even_and_after_odd(array, count));
        return 0;
    default:
        printf("Данные некорректны\n");
        return 0;
    }

}
