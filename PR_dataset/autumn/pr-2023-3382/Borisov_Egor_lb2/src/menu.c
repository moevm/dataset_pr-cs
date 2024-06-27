#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"

int main()
{
    int operation;
    int massive[100];
    int i = 0;
    int answer = 0;
    char space;
    int len = 0;
    scanf("%d%c", &operation, &space);
    do
    {
        scanf("%d%c", &massive[len], &space);
        len++;
    } while(space != '\n');

    switch(operation){
        case 0:
            answer = index_first_zero(massive, i, len);
            printf("%d", answer);
            break;
        case 1:
            answer = index_last_zero(massive, i, len);
            printf("%d", answer);
            break;
        case 2:
            answer = sum_between(massive, i, len);
            printf("%d", answer);
            break;
        case 3:
            answer = sum_before_and_after(massive, i, len);
            printf("%d", answer);
            break;
        default:
            puts("Данные некорректны");
    }
    return 0;
}

