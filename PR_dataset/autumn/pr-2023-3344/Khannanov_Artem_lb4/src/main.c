#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define LENGTH 1000

int abs_sort( const void * val1, const void * val2 );
//void decimal_generator(int array[]); // функция генерирует рандомные числа для проверки работы программы


int main() {

    int array[LENGTH];

    //decimal_generator(array); // радномная генерация с помощью функции
    for (size_t i = 0; i < LENGTH; i++) scanf("%d", &array[i]); // считывание введённых чисел и запись в массив

    clock_t start = clock(); // начало отсчёта времени
    qsort(array, LENGTH, sizeof(int), abs_sort); // сортировка массива
    clock_t end = clock(); // окончание отсчёта времени

    for (size_t i = 0; i < LENGTH; i++) printf("%d ", array[i]); // вывод отсортированного массива
    
    printf("\n%f", (double)(end - start) / CLOCKS_PER_SEC); // вывод времени    

    return 0;
}


int abs_sort( const void * val1, const void * val2 ) {
    return (abs(*(int *)val2) - abs(*(int *)val1));
}


/*
void decimal_generator(int array[]) {
    for (size_t i = 0; i < LENGTH; i++) array[i] = rand() % 2001 - 1000;
}
*/