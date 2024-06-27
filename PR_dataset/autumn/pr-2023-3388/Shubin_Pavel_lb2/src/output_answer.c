#include <stdio.h>
#include "output_answer.h"

void output_answer(int answer){
        if (answer == -1){
            printf("Данные некорректны\n");
        }
        else{
            printf("%d\n", answer);
        }
}