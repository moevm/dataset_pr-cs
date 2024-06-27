#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include "structs.h"

int func_sum_of_minutes(struct Text text){
    int sum = 0; 
    int position, start, len, flag;
    wchar_t* result;
    wchar_t* str;
    wchar_t* search = L" sec ";
    for (int i = 0; i < text.count_of_sentences; i++){
        str = text.list_of_sentences[i].sentence;
        while (wcsstr(str, search) != NULL){
            flag = 1;
            result = wcsstr(str, search);
            position = result - str;
            start = position - 1;
            while (1)
            {
                if (iswdigit(str[start]))
                    start--;
                else{
                    if (str[start] != L' ')
                        flag = 0;
                    start++;
                    break;
                }
            }
            if (start <= position - 1 && flag == 1){
                char* number = calloc(position - start + 1, sizeof(char));
                for (int x = 0; x < (position - start); x++){
                    number[x] = str[start + x];
                }
                sum += atoi(number);
                free(number);
            }
            str = wcsstr(str, search) + 5;
        }
    }
    sum = sum / 60;
    return sum;
}