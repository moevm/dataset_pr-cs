#include <stdio.h>
#define OUTPUTSTRING "%d\n"
#define SIZE 100
int max(int arr[], int size);
int min(int arr[], int size);
int diff(int arr[], int size);
int sum(int arr[], int size);
int input(int arr[], int *size);
void answer();
int main(){
    answer();
    return 0;
}
// Функция для поиска максимального числа в массиве
int max(int arr[], int size)
{
    int max_element = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] > max_element)
        {
            max_element = arr[i];
        }
    }
    return max_element;
}
// Функция для поиска минимального числа в массиве
int min(int arr[], int size)
{
    int min_element = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i] < min_element)
        {
            min_element = arr[i];
        }
    }
    return min_element;
}
// Функция для расчета разницы между максимальным и минимальным элементом массива
int diff(int arr[], int size)
{
    return max(arr, size) - min(arr, size);
}

// Функция для расчета суммы элементов массива до первого минимального элемента
int sum(int arr[], int size)
{
    int min_element = min(arr, size);
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == min_element)
        {
            break;
        }
        sum += arr[i];
    }
    return sum;
}
int input(int arr[], int *size){
    *size = -1;
    while ((*size) < 99 && scanf("%d", &arr[++(*size)]) == 1);
}
void answer(){
    int choice;
    int arr[SIZE];
    int size, i;

    // Ввод значения choice (0,1,2 или 3)
    scanf("%d", &choice);
    input(arr, &size);
    switch (choice){
        case 0:
            printf(OUTPUTSTRING, max(arr, size));
            break;
        case 1:
            printf(OUTPUTSTRING, min(arr, size));
            break;
        case 2:
            printf(OUTPUTSTRING, diff(arr, size));
            break;
        case 3:
            printf(OUTPUTSTRING, sum(arr, size));
            break;
        default:
            printf("Данные некорректны\n");
            break;
    }
}