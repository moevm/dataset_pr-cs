#include "check_cyrillic.h"
#include <wchar.h>
#include <wctype.h>

int check_cyrillic(wchar_t** split_sent, size_t len){
    int flag = 1;
    for (int i = 0;i<len;i++){
        size_t count = 0;
        for (int j = 0;j<wcslen(split_sent[i]);j++){

            if ((split_sent[i][j]>=L'А' && split_sent[i][j]<=L'Я')||(split_sent[i][j]>=L'а' && split_sent[i][j]<=L'я')|| (iswpunct(split_sent[i][j])==1)|| (iswdigit(split_sent[i][j]))==1){
                count++;
            }

        }
        if (count!=wcslen(split_sent[i])){
            flag = 0;
        }
    }
    return flag;
}