#include <stdio.h>
#include<stdlib.h>
#include"index_first_negative.h"
#include"index_last_negative.h"
#include"sum_between_negative.h"
#include"sum_before_and_after_negative.h"

int main()
{
    int array[100];
    char enter;
    int input;
    int array_length = 0;
    scanf("%d", &input);
    for(int i=0; i<100; i++)
    {
        scanf("%d%c", &array[i], &enter);
        array_length++;
        if (enter == '\n')
        break;
    }
    switch(input)
    {
    	case 0:
        printf("%d\n", index_first_negative(array, array_length));
        break;

        case 1:
        printf("%d\n", index_last_negative(array, array_length));
        break;

        case 2:
        printf("%d\n", sum_between_negative(array, array_length));
        break;

        case 3:
        printf("%d\n", sum_before_and_after_negative(array, array_length));
        break;
        default:
        printf("Данные некорректны\n");
        break;
    }
 return 0;
}