#include <stdio.h>
#include <stdlib.h>

int main() {
    int index_first_even(int array[]) {
        int i = 0;
        while (array[i] % 2 != 0) {
            i++;
        }
        return i;
    }

    int index_last_odd(int array[], int count) {
        while (array[count-1] % 2 == 0) {
            count--;
        }
        return count-1;
    }

    int sum_between_even_odd(int array[], int count) {
        int result = 0;
        for (int i = index_first_even(array); i < index_last_odd(array, count); i++) {
            result += abs(array[i]);
        }
        return result;
    }

    int sum_before_even_and_after_odd(int array[], int count) {
        int result = 0;
        for (int i = 0; i < index_first_even(array); i++) {
            result += abs(array[i]);
        }
        for (int i = index_last_odd(array, count); i < count; i++) {
            result += abs(array[i]);
        }
        return result;
    }

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
