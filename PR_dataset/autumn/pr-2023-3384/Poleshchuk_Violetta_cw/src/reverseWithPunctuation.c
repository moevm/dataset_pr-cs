#include <wchar.h>
#include <stdio.h>
#include "header_files/structures.h"
#include "header_files/reverseWithPunctuation.h" 

void reverseWithPunctuation(Text text){
    for (int i = 0; i < text.countSentences; i++){
        for (int j = text.sentences[i].counterWords-1; j >= 0; j--){
            if (j > 0){
                wprintf(L"%ls%ls", text.sentences[i].words[j].symbols, text.sentences[i].words[j-1].punctuation);
            }
            else{
                wprintf(L"%ls.", text.sentences[i].words[j].symbols);
            }
        }
        wprintf(L"\n");
    }
}