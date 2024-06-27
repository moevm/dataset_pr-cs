#include "Common.h"
#include "Function8.h"

int count_sum_of_digits(char* str){
    int sum = 0;
    for (int i = 0; str[i]!=0;i++){
        if ((str[i]>=49)&&(str[i]<=57)) sum += str[i]-48;
    }

    return sum;
}
void function8(char** text){
    int compare = count_sum_of_digits(text[0]);
    for (int i = 1; text[i]!=0;i++){
        int diff = count_sum_of_digits(text[i])-compare;
        if (diff > 0){
            printf("(%d) %s\n", diff, text[i]);
        }
    }
}
