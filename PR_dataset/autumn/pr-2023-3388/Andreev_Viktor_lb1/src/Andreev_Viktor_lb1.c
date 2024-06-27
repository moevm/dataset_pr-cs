#include <stdio.h>
#include <stdlib.h>


// Поиск индекса первого четного элемента массива
int index_first_even(int arr[], int n) {
    for (int i = 0; i < n; i = i + 1) {
        if(arr[i] % 2 == 0) {
            return i;
        }
    }
}

// Поиск индекса последнего нечетного элемента массива
int index_last_odd(int arr[], int n) {
    for (int i = n - 1; i >= 0; i = i - 1) {
        if(arr[i] % 2 != 0) {
           return i;
        }
    }
}

// Сумма модулей эл-ов массива, от первого четного эл-а до последнего нечетного эл-а
int sum_between_even_odd(int arr[], int n) {
    // first - индекс первого четного эл-та
    // last - индекс последнего нечетного эл-та
    int i, first, last, summ = 0;
    
    first = index_first_even(arr, n);
    last = index_last_odd(arr, n);
    
    for (int i = first; i < last; i = i + 1) {
        summ = summ + abs(arr[i]);
    }
    return summ;
}

// Сумма модулей эл-ов массива, от первого эл-ма массива до первого четного 
// и от последнего нечетного до последнего эл-та массива
int sum_before_even_and_after_odd(int arr[], int n) {
    // first - индекс первого четного эл-та
    // last - индекс последнего нечетного эл-та
    int i, first, last, summ = 0;
    
    first = index_first_even(arr, n);
    last = index_last_odd(arr, n);
    
    for (int i = 0; i < first; i = i + 1) {
        summ = summ + abs(arr[i]);
    }
    for (int i = last; i < n; i = i + 1) {
        summ = summ + abs(arr[i]);
    }
    return summ;
}



int main()
{
    // k - аргумент, n - длинна массива
    int k, n = 100, i = 0;
    int arr[n];
    char c;
    
    // Считываем массив целых чисел и аргумент k
    scanf("%d", &k);
    while(c!='\n') {
        scanf("%d%c", &arr[i], &c);
        i++;
    }
    n = i;
    
    // Вывод ответа в зависимости от аргумента k
    switch (k) {
        case 0: printf("%d\n", index_first_even(arr, n)); break;
        case 1: printf("%d\n", index_last_odd(arr, n)); break;
        case 2: printf("%d\n", sum_between_even_odd(arr, n)); break;
        case 3: printf("%d\n", sum_before_even_and_after_odd(arr, n)); break;
        default: printf("Данные некорректны"); break;
        }
    return 0;
}
