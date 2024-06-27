#include <stdio.h>

#define     N       20

int index_first_negative(int masive[], int countElements) {
    
    for(int i = 0; i < countElements; i++) {
        if (masive[i] < 0)
            return i;
    }
}

int index_last_negative(int masive[], int countElements) {
    
    for(int i = countElements-1; i >= 0; i--) {
        if (masive[i] < 0)
            return i;
    }
    
}

int multi_between_negative(int masive[], int a, int b) {
    int rez = 1;
    for(int i = a; i < b; i++)
        rez *= masive[i];
        
    return rez;
}

int multi_before_and_after_negative(int masive[], int a, int b, int countElements) {
    int rez = 1;
    for(int i = 0; i < a; i++)
        rez *= masive[i];
    for(int i = b; i < countElements; i++)
        rez *= masive[i];
    
    return rez;
}

int main() {
    int number = -1;
    char symbol;
    int masive[N];
    int countElements = 0; // счетчик элементов в массиве
    
    while (symbol != '\n') {
        if (number != -1)
            scanf("%d%c", &masive[countElements], &symbol);
        else
            scanf("%d%c%d%c", &number, &symbol, &masive[countElements], &symbol);
        countElements++;
    }
    
    switch (number) {
        case 0 :
            printf("%d\n", index_first_negative(masive, countElements)); // индекс первого отрицательного
            break;
        case 1:
            printf("%d\n", index_last_negative(masive, countElements)); // индекс последнего отрицательного
            break;
        case 2:
            printf("%d\n", multi_between_negative(masive, index_first_negative(masive, countElements), index_last_negative(masive, countElements))); // произведение между отрицательными
            break;
        case 3:
            printf("%d\n", multi_before_and_after_negative(masive, index_first_negative(masive, countElements), index_last_negative(masive,countElements), countElements)); // произведение вне крайних элементов
            break;
        default:
            puts("Данные некорректны\n");
    }
    
    return 0;
}
