#include <stdio.h>

#define N 100 // Максимальное количество введённых чисел

int get_max_arr(int array[], int length); // возвращает максимальное число из переданного массива
int get_min_arr(int array[], int length); // возвращает минимальное число из переданного массива
int get_diff_max_min_arr(int array[], int length); // возвращает разницу максимального и минимального числа из переданного массива
int get_sum_before_min(int array[], int length); // возвращает сумму чисел до первого вхождения минимального числа в переданном массиве
void print_answer(int number, int array[], int length); // выводит ответ в консоль в зависимости от выбора режима программы и введённого массива пользователем

// для всех функций: array[] - поданный на вход массив чисел; length - количество введённых чисел
// для всех циклов счётчиком является переменная i И j 

int main(){
    int chose, arr[N], i = 0; // chose - переменная выбора задачи программы; arr[N] - получаемый от пользователя массив чисел
    char space = ' '; // space - переменная для проверки перехода записи в следующую ячейку массива
    scanf("%d", &chose); // выбор пользователем режима программы
    while (i < N && space == ' ') { // цикл ввода массива
        scanf("%d%c", &arr[i], &space); 
        i++;
    }
    print_answer(chose, arr, i);
    return 0; // корректно завершает работу программы
}

int get_max_arr(int array[], int length){
    int answer = 0;
    for (int j = 0; j < length; j++){ // цикл поиска максимального значения в переданном массиве
        if (array[j] > answer){
            answer = array[j];
        }
    }
    return answer;
}

int get_min_arr(int array[], int length){
    int answer = 10000000; // потенциальное число, больше которого в массиве нет
    for (int j = 0; j < length; j++){ // цикл поиска минимального значения в переданном массиве
        if (array[j] < answer){
            answer = array[j];
        }
    }
    return answer;
}

int get_diff_max_min_arr(int array[], int length){
    return get_max_arr(array, length)-get_min_arr(array, length);
}

int get_sum_before_min(int array[], int length){
    int sum = 0, min = get_min_arr(array, length), j = 0; // min - переменная, хранящая величину минимального числа в массиве
    while(array[j] > min){ // проверка на первое вхождение минимального числа в массиве
        sum += array[j]; // посчёт суммы
        j++;
    }
    return sum;
}

void print_answer(int number, int array[], int length){ // number - переменная, хранящая число, введённое пользователем для выбора режима программы
    switch (number){ // ветвление в зависимости от выбоар пользователя
        case 0:
            printf("\n%d\n", get_max_arr(array, length));
            break;
        case 1:
            printf("%d\n", get_min_arr(array, length));
            break;
        case 2:
            printf("%d\n", get_diff_max_min_arr(array, length));
            break;
        case 3:
            printf("%d\n", get_sum_before_min(array, length));
            break;
        default: // ошибочный ввод от пользователя
            printf("Данные некорректны\n"); 
    }
}