#include <stdio.h>
#include "index_first_negative.h"
#include "index_last_negative.h"
#include "multi_between_negative.h"
#include "multi_before_and_after_negative.h"
#define mas 20
int main()
{
    int a[mas];
    int data;
    int count=0;
    char other;
    scanf("%d", &data);
  while(count<mas){
        scanf("%d", &a[count]);
        count++;
        if (getchar() == '\n'){
            break;
        }
    }
    switch (data)
    {
    case 0:
        printf("%d\n", index_first_negative(a, count));
        break;
    case 1:
        printf("%d\n", index_last_negative(a, count));
        break;
    case 2:
        printf("%d\n", multi_between_negative(a, count));
        break;
    case 3:
        printf("%d\n", multi_before_and_after_negative(a, count));
        break;
    default:
        printf("Данные некорректны\n");

    }
    return 0;
}