#include <stdio.h>
#define MAX_SIZE 100

// Объявление прототипов функций
int max (int * date, char size);
int min (int * date, char size);
long int diff (int * date, char size);
long int sum (int * date, char size);

int main() {
    
    // Чтение данных
    int input[MAX_SIZE];
    char operation;
    scanf("%hhd", &operation);
    char simbol = 0;
    char size = 0;
    for (char a = 0; a < MAX_SIZE; a++){
        scanf("%d%c", &input[a], &simbol);
        if (simbol == '\n'){
            size = a+1;
            break;
        }
    }

    // Обработка входных данных 
    switch (operation) {
        case 0:
            printf("%d\n", max(input, size));
            break;
        case 1:
            printf("%d\n", min(input, size));
            break;
        case 2:
            printf("%ld\n", diff(input, size));
            break;
        case 3:
            printf("%ld\n", sum(input, size));
            break;
        default:
            printf("Данные некорректны\n");
            return 0;
    }
     
    return 0;
}

// Описание функций

int max (int * date, char size) {
    int result = date[0];
    for (char a = 1; a < size; a++)
        result = (date[a] > result) ? date[a] : result;
    return result;
}

int min (int * date, char size) {
    int result = date[0];
    for (char a = 1; a < size; a++)
        result = (date[a] < result) ? date[a] : result;
    return result;
}

long int diff (int * date, char size){
    return (long int) max(date, size) - min(date, size);
}

long int sum (int * date, char size) {
    int minimum = min(date, size);
    long int result = 0;
    for (char a = 0; a<size; a++){
        if (date[a] == minimum)
            break;
        result += date[a];
    }
    return result;
}
