#include <stdlib.h>
#include <string.h>
#include "../header/removeDuplicates.h"

void rmDup(char** text, int* sent_num){
    int origin_sent_count=0;
    for (int i = 0; i < *sent_num; ++i) {
        if (text[i]==NULL){
            continue;
        }
        for (int j = 0; j < *sent_num; ++j) {
            if (text[j]==NULL){
                continue;
            }
            if (strcasecmp(text[i], text[j])==0 && i!=j){
                text[j]=NULL;
                origin_sent_count++;
            }
        }
    }
}