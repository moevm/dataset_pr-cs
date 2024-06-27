#include <stdio.h>
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"

int main(){
    int array[100];
    int number;
    int command;
    int len = 0;
    scanf("%d", &command);
    while (getchar() != '\n'){
        scanf("%d", &number);
        array[len] = number;
        len++;
    }
    
    switch (command){
    case 0:
        printf("%d\n", max(array, len));
        break;
    case 1:
        printf("%d\n", min(array, len));
        break;
    case 2:
        printf("%d\n", diff(array, len));
        break;
    case 3:
        printf("%d\n", sum(array, len));
        break;
    default:
        printf("Данные некорректны\n");
    }
    return 0;
}
