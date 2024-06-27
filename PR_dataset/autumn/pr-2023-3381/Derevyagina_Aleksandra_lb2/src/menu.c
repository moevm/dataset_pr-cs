#include <stdio.h>
#define N 100
#include "max.h"
#include "min.h"
#include "diff.h"
#include "sum.h"

int main(){
    int operationValue;
    int array[N];
    int elementIndex = 0;
    scanf("%d", &operationValue);
    while (elementIndex < N) {
        scanf("%d", &array[elementIndex]);
        elementIndex++;
        if (getchar() == '\n') {
            break;
        }
    }
    switch (operationValue){
        case 0:
            printf("%d\n", max(array, elementIndex));
            break;
        case 1:
            printf("%d\n", min(array, elementIndex));
            break;
        case 2:
            printf("%d\n", diff(array, elementIndex));
            break;
        case 3:
            printf("%d\n", sum(array, elementIndex));
            break;
        default:
            printf("Данные некорректны\n");
    };
    return 0;
}

