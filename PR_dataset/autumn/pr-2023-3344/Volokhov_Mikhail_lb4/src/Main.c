#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Сравнивает два элемента для qsort
int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    // Выделяем память под 1000 чисел
    int* array = (int*)malloc(1000 * sizeof(int));

    // Ввод
    for (int i = 0; i < 1000; i++) {
        scanf("%d", &array[i]);
    }

    // Засекаем время начала сортировки
    clock_t start_time = clock();

    // Сортируем массив
    qsort(array, 1000, sizeof(int), compare);

    // Время окончания сортировки
    clock_t end_time = clock();

    // Вывод отсортированного массива
    for (int i = 0; i < 1000; i++) {
        printf("%d ", array[i]);
    }

    // Вывод времени сортировки
    printf("\n%f\n", ((double)end_time - start_time) / CLOCKS_PER_SEC);
    free(array);

    return 0;
}