#include "Free.h"

void freeText(char **text, int len){
        for (int i = 0; i < len; i++){
                free(text[i]);
        }
        free(text);
}

