#include "First_vowel.h"

char **First_vowel(int *len, char** text){
        int new_len = *len;
        int clause = 0;
        for(int i = 0; i < new_len; i++){
                if (isalpha(text[i][0])){
                        if(toupper(text[i][0])  == 'A' || toupper(text[i][0])  == 'E' || toupper(text[i][0])  == 'I' || toupper(text[i][0])  == 'O' ||toupper(text[i][0])  == 'U' || toupper(text[i][0])  == 'Y'){
                                clause = 1;
                        }
                }
                if (isdigit(text[i][0])){
                        clause = 1;
                }
                if (clause == 0){
                        Delete_sent(text, new_len, i);
                        new_len--;
                        i--;
                        *len = new_len;
                }
                clause = 0;
        }
        return text;
}

