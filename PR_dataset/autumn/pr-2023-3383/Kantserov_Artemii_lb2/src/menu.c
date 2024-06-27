#define MAX_SIZE 100

#include <stdio.h>
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"

int main() {
    
    // Чтение данных
    int input[MAX_SIZE];
    char operation;
    scanf("%hhd", &operation);
    char simbol = 0;
    char size = 0;
    for (char i = 0; i < MAX_SIZE; i++){
        scanf("%d%c", &input[i], &simbol);
        if (simbol == '\n'){
            size = i+1;
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
