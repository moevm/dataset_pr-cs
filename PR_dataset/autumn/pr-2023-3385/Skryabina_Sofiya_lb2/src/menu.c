#include <stdio.h>
#include <stdlib.h>
#include "index_first_even.h"
#include "index_last_odd.h"
#include "sum_between_even_odd.h"
#include "sum_before_even_and_after_odd.h"

int main(){
    int mas[100], value, len=0;
    char stop;
    scanf("%d", &value);
    for(int i=0; i < 100; i++)
  {
        scanf("%d%c", &mas[i], &stop);
        len++;
        if (stop=='\n') break;
  }
    switch(value){
        case 0:
            printf("%d\n", index_first_even(mas, len));
            break;
        case 1:
            printf("%d\n", index_last_odd(mas, len));
            break;
        case 2:
            printf("%d\n", sum_between_even_odd(mas, len));
            break;
        case 3:
            printf("%d\n", sum_before_even_and_after_odd(mas, len));
            break;
        default:
            printf("Данные некорректны");
    }
}
