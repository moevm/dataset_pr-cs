#include <stdio.h>
#include <stdlib.h>
#include "index_first_zero.h"
#include "index_last_zero.h"
#include "sum_between.h"
#include "sum_before_and_after.h"
#include "switchfunc.h"
#define ERR -1
#define OUTPUT_ERR "Данные некорректны"
void switchfunc(int variant){
	switch(variant){
        case 0:
            if (index_first_zero(chisla,len) == ERR){
                printf("%s\n", OUTPUT_ERR);
            }
            else{
                printf("%d\n", index_first_zero(chisla,len));
            }
            break;
        case 1:
            if (index_last_zero(chisla,len) == ERR){
                printf("%s\n", OUTPUT_ERR);
            }
            else{
                printf("%d\n", index_last_zero(chisla,len));
            }
            break;
        case 2:
            if (sum_between(chisla, len) == ERR){
                printf("%s\n", OUTPUT_ERR);
            }
            else{
                printf("%d\n", sum_between(chisla, len));
            }
            break;
        case 3:
            if (sum_before_and_after(chisla, len) == ERR){
                printf("%s\n", OUTPUT_ERR);
            }
            else{
                printf("%d\n", sum_before_and_after(chisla, len));
            }
            break;
        default:
           printf("%s\n", OUTPUT_ERR);
    }
}