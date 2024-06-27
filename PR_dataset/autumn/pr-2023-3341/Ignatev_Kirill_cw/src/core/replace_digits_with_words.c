#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void replaceDigitsWithWords(char** split_text, int *sent_num){
    const char* words[] = {"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    for (int i=0; i< *sent_num; i++){
        if (split_text[i]!=NULL){
            size_t len = strlen(split_text[i]);
            char* result=malloc(len*5+1);
            size_t resultIndex=0;
            for (int j = 0; j < len; ++j) {
                if (isdigit(split_text[i][j])){
                    int digit=split_text[i][j]-'0';
                    if (digit >= 0 && digit <= 9){
                        const char* word = words[digit];
                        size_t wordLen = strlen(word);
                        strncpy(&result[resultIndex], word, wordLen);
                        resultIndex+=wordLen;
                    }
                }else{
                    result[resultIndex++]=split_text[i][j];
                }
            }
            result[resultIndex]='\0';
            split_text[i]=result;
        }
    }
}