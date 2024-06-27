#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "../header/only_num.h"

void onlyNum(char** split_text, int* sent_num){
    for (int i = 0; i < *sent_num; ++i) {
        int flag = 1;
        if (split_text[i]!=NULL){
            for (int j = 0; j < strlen(split_text[i]); ++j) {
                if (isalpha(split_text[i][j]) && isspace(split_text[i][j])==0)
                    flag = 0;
            }
            if (flag==0){
                split_text[i]=NULL;
            }
        }
    }
}