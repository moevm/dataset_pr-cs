#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"

int main()
{
    int type;
    int last_elem = 0;
    scanf("%d", &type);
    int array[20];

    for (int i = 0; i < 20; i++)
    {
        last_elem++;
        if (scanf("%d", &array[i]) == 0 || getchar() == '\n')
        {
            break;
        }
    }

    switch (type)
    {
    case 0:
        printf("%d\n", index_first_negative(array, last_elem));
        break;
    case 1:
        printf("%d\n", index_last_negative(array, last_elem));
        break;
    case 2:
        printf("%d\n", multi_between_negative(array, last_elem));
        break;
    case 3:
        printf("%d\n", multi_before_and_after_negative(array, last_elem));
        break;
    default:
        printf("Данные некорректны");
        break;
    }

    return 0;
}