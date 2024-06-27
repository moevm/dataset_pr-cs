#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "sum_between_negative.h"
#include "sum_before_and_after_negative.h"

int main()
{
    int number;
    scanf("%d", &number);
    int mas[100];
    int i=-1;
    while (getchar()!='\n'){
        i++;
        if (i==100){
            puts("Данные некорректны\n");
            return 0;
        }
        scanf("%d", &mas[i]);
    }
    int ln = i+1;
    switch (number){
        case 0:
            printf("%d\n",index_first_negative(mas, ln));
            break;
        case 1:
            printf("%d\n",index_last_negative(mas, ln));
            break;
        case 2:
            printf("%d\n",sum_between_negative(mas, ln));
            break;
        case 3:
            printf("%d\n",sum_before_and_after_negative(mas, ln));
            break;
        default:
            puts("Данные некорректны\n");
    }
    
}
