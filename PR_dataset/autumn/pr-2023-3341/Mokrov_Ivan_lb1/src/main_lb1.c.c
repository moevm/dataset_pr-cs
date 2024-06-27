#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// размер максимального массива
#define ARRAY_SIZE 20
#define INPUT_SIZE 50
#define out "%d\n"

int finite_array[ARRAY_SIZE]; // массив для обработки
int size; // Размер для обрабатываемого массива 
char value; //  Код обработки


    
// индекс первого отрицательного элемента
int index_first_negative(int array[], int size){ 
    for (int i = 0; i < size; i++) {
        if (array[i] < 0) {
            return i;
        }
    }
}


// индекс последнего отрицательного элемента
int index_last_negative(int array[], int size){
    for (int i = size; i >= 0; i--) {
        if (array[i] < 0) {
            
            return i;
        }
    }
}

// Найти произведение элементов массива, расположенных от первого отрицательного элемента  и до последнего отрицательного
int multi_between_negative(int array[], int size){
    int first = index_first_negative(array, size);
    int last = index_last_negative(array, size);
    
    int return_index = 1;
    
    for (int i = first; i < last; i++) {
        return_index *= array[i];
    }
    return return_index;
}

// Найти произведение элементов массива, расположенных до первого отрицательного элемента и после последнего отрицательного
int multi_before_and_after_negative(int array[], int size){
    int first = index_first_negative(array, size);
    int last = index_last_negative(array, size);
    
    int return_index = 1;
    
    for (int i = 0; i < first; i++) {
        return_index *= array[i];
    }
    for (int i = last; i < size; i++) {
        return_index *= array[i];
    }
    return return_index;
}

// Удаление пробелов, и запись массив в числовой параметр 
void clear_array(char array[], int finite_array[], int *size){
    char *array_str;
    array_str = strtok(array, " ");
    array_str = strtok(NULL, " ");

    while (array_str != NULL) {
        finite_array[(*size)++] = atoi(array_str);
        array_str = strtok(NULL, " ");
    }
}

void input_data(){
     // ввод значения с терминала
    char received_array[INPUT_SIZE];
    fgets(received_array, INPUT_SIZE, stdin);
    
    // Отделения значения для запроса
    value = received_array[0];
    
    clear_array(received_array, finite_array, &size);
}

void request_processing(int request){
    
    // Обработка массива по задоному коду и вывод на экран
    switch(request)
    {
        case '0':
            printf(out, index_first_negative(finite_array, size));
            break;
        
        case '1':
            printf(out,index_last_negative(finite_array, size));
            break;
        
        case '2':
            printf(out,multi_between_negative(finite_array, size));
            break;
            
        case '3':
            printf(out,multi_before_and_after_negative(finite_array, size));
            break;
        
        default:
            printf("Данные некорректны");
            break;
    
    }
}

int main()
{
   
    input_data();
    request_processing(value);
    return 0;
}
    