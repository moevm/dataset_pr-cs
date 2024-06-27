#include "../header/del_sent_by_word.h"
#include <string.h>

void delSentByWord(char** split_text, char* keyword, int* sent_num){

    size_t len= strlen(keyword);
    for (int i = 0; i < *sent_num; ++i) {
        if (split_text[i]!=NULL){
            int count = 0;
            char* pos=(char *)split_text[i];
            while ((pos = strstr(pos,keyword))!=NULL){
                count++;
                pos+=len;
            }
            if (count>=2){
                split_text[i]=NULL;
            }
        }
    }
}