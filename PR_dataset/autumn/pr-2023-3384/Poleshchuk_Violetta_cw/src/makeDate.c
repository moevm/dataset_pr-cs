#include <stdio.h>
#include <wctype.h>
#include "header_files/structures.h"
#include "header_files/makeDate.h"
void makeDate(Text text){
    int maxLen = 0;
    for (int i = 0; i < text.countSentences; i++){
        for (int j = 0; j < text.sentences[i].counterWords; j++){
            if (text.sentences[i].words[j].len > maxLen) maxLen = text.sentences[i].words[j].len;
        }
        wprintf(L"%ls [%d-%d-%d]\n", text.sentences[i].content, text.sentences[i].counterWords, maxLen, 1900+text.sentences[i].len);
    }
}