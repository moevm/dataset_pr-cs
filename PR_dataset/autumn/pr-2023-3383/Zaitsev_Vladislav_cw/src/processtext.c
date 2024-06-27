#include "processtext.h"

char **processText(int *len, char **text){
        int new_len = *len;
        for (int i = 0; i < new_len; i++){
                for (int j = 0; j < i; j++){
                        if (strcmp(text[i], text[j]) == 0){
                                Delete_sent(text, new_len, i);
                                i--;
                                new_len--;
                                *len = new_len;
                        }
                }
        }
        return text;
}

