#include <stdio.h>
#include "header_files/delete.h"
#include "header_files/structures.h"

void delete(Text text){
    for (int i = 0; i < text.countSentences; i++){
        int counterWordsLenLess3 = 0;
        for (int j = 0; j < text.sentences[i].counterWords; j++){
            if (text.sentences[i].words[j].len <= 3){
                counterWordsLenLess3 += 1;
                continue;
            }
        }
        if (!(counterWordsLenLess3 == text.sentences[i].counterWords)){
            wprintf(L"%ls\n", text.sentences[i].content);
        }
    }
}