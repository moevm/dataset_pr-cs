#include "Delete_13.h"

char** Delete_13(int *len, char **text){
        int new_len = *len;
        int count = 0;
        for (int i = 0; i < new_len;i++){
                for (int j = 0; j < strlen(text[i]); j++){
                                if(isdigit(text[i][j])){
                                        char buff[2];
                                        buff[0] = text[i][j];
                                        buff[1] = '\0';
                                        count += atoi(buff);
                                }
                }
                if (count == 13){
                        Delete_sent(text, new_len, i);
                        i--;
                        new_len--;
                        *len = new_len;
                }
                count = 0;
        }
        return text;
}
