#include <stdio.h>
#include <time.h>

#define N 1000
clock_t bubble(int* arr, int size) {
    clock_t time_start_bubble = clock();
    for (int i = size; i >= 0; i--) {
        for (int j = 1; j < i; j++) {
            if (arr[j] >= arr[j - 1]) {
                int temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
    return (clock() - time_start_bubble);
}

//вспомогательная функция для qsort
int cmp(const void* a, const void* b) {
    const int* f = (const int*)a;
    const int* s = (const int*)b;
    if (*f > *s) {
        return 1;
    }
    if (*f < *s) {
        return -1;
    }
    return 0;
}

int main() {
    int arr[N]; //определяем массив 
    for (int i = 0; i < N; i++) { //заполняем массив цифрами
        scanf("%d", &arr[i]);
    }
    
    //вводим переменную, отвечающую за время сортировки пузырьком
    clock_t time_to_bubble = bubble(arr,N);
    
    //считаем время работы qsort
    clock_t time_qsort_start = clock();
    qsort(arr, N, sizeof(int), cmp);
    clock_t time_to_qsort = clock() - time_qsort_start;

    //выводим массив цифр
    for (int i = 0; i < N; i++) {
        printf("%d ", arr[i]);
    }
    printf("%c", '\n');
    //выводим время работы функции bubble
    printf("%f \n", (float)time_to_bubble / CLOCKS_PER_SEC);
    //выводим время работы qsort
    printf("%f \n", (float)time_to_qsort / CLOCKS_PER_SEC);

    return 0;
}