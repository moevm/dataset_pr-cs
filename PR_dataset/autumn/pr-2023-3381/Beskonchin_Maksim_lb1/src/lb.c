#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

//Функция нахождения индекса первого нулевого элемента
int index_first_zero(int len_a ,int a[]){
    for (int index = 0; index < len_a; index++){
    if (a[index] == 0)
        return index;}
return -1;
}

//Функция нахождения индекса последнего нулевого элемента
int index_last_zero(int len_a ,int a[]){
    int index = -1;
for (int index_for = 0; index_for < len_a; index_for++){
        if (a[index_for] == 0)
    index = index_for;
}
return index;
}

//Функция нахождения суммы модулей элементов массива, расположенных от первого нулевого элемента и до последнего
int sum_between(int len_a ,int a[], int index_first_funct, int index_last_funct){
    int sum_array = 0;
    for(;index_first_funct<index_last_funct;index_first_funct++)
        sum_array += abs(a[index_first_funct]);
return sum_array;
}

//Функция нахождения суммы модулей элементов массива, расположенных до первого нулевого элемента и после последнего
int sum_before_and_after(int len_a ,int a[], int index_first_funct, int index_last_funct){
    int sum_array = 0;
    for(int i = 0; i < index_first_funct; i++)
        sum_array += abs(a[i]);
    for(; index_last_funct < len_a; index_last_funct++)
        sum_array += abs(a[index_last_funct]);
return sum_array;
}



int main()
{
setlocale(LC_ALL, "Rus"); // Функция для коректного вывода кирилицы
int number;
scanf("%d", &number);
int array[100]; // Объявляем массив
int len_array = 0; // Переменная для отслеживания длины массива

    // Считываем числа до символа перевода строки или пока не заполним массив
    while (len_array < 100) {
        int num;
        if (scanf("%d", &num) == 1) {
            array[len_array] = num;
            len_array++;
        } else {
            break;
        }
    }

int first_zero = index_first_zero(len_array, array); // Индекс первого нулевого элемента
int last_zero = index_last_zero(len_array, array); // Индекс последнего нулевого элемента

if (last_zero == -1 || first_zero == -1 || first_zero >= last_zero) { // Проверка данных
printf("Данные некорректны\n");
return 0;
}
// В зависимости от значения, функция выводит следующее:

switch(number){
case 0:
    printf("%d\n", first_zero);
    break;
case 1:
        printf("%d\n", last_zero);
    break;
case 2:
    printf("%d\n", sum_between(len_array, array,first_zero,last_zero));
    break;
case 3:
    printf("%d\n", sum_before_and_after(len_array, array,first_zero,last_zero));
    break;
default:
    puts("Данные некорректны");
break;
}
return 0;
}
