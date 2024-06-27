#include <stdio.h>
#include <stdlib.h>

int index_first_even(int array[], int size_array);
int index_last_odd(int array[], int size_array);
int sum_between_even_odd(int array[], int size_array);
int sum_before_even_and_after_odd(int array[], int size_array);

int main(){
    char sym;
    int option, arr[100], size_arr = 0;
    scanf("%d%c", &option, &sym); // Выбор варианта
    for(int i = 0; i < 100; i++){
        scanf("%d%c", &arr[i], &sym);
        size_arr++;
        if (sym == '\n'){ // Проверка на конец ввода
            break;
        }
        
    }
    switch(option){
        case 0:
            printf("%d\n", index_first_even(arr, size_arr));
            break;
        case 1:
            printf("%d\n", index_last_odd(arr, size_arr));
            break;
        case 2:
            printf("%d\n", sum_between_even_odd(arr, size_arr));
            break;
        case 3:
            printf("%d\n", sum_before_even_and_after_odd(arr, size_arr));
            break;
        default:
            printf("Данные некорректны\n");
    }
    return 0;
}

int index_first_even(int array[], int size_array){ // Индекс первого чётного элемента
    for(int i = 0; i < size_array; i++){
        if(array[i] % 2 == 0){
            return i;
            break;
        }
    }
}

int index_last_odd(int array[], int size_array){ // Индекс последнего нечётного элемента
    for(int i = size_array - 1; i >= 0; i--){
        if(array[i] % 2 != 0){
            return i;
            break;
        }
    }
}

int sum_between_even_odd(int array[], int size_array){ // Сумма модулей элементов массива, расположенных от первого чётного элемента и до последнего нечётного, включая первый и не включая последний
    int sum = 0; 
    int start = index_first_even(array, size_array); 
    int end = index_last_odd(array, size_array);
    if (start < end){
        for(int i = start; i < end; i++)
            sum += abs(array[i]);
    } else{
        for(int i = end + 1; i <= start; i++)
            sum += abs(array[i]);
    }
    return sum;
}

int sum_before_even_and_after_odd(int array[], int size_array){ // Сумма модулей элементов массива, расположенных до первого чётного элемента (не включая элемент) и после последнего нечётного (включая элемент)
    int sum = 0; 
    int start = index_first_even(array, size_array); 
    int end = index_last_odd(array, size_array);
    for(int i = 0; i < start; i++)
        sum += abs(array[i]);
    for(int i = end; i < size_array; i++)
        sum += abs(array[i]);
    return sum;
}
