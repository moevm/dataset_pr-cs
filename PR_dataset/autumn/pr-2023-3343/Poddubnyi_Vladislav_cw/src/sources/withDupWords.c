//
// Created by rect on 23.11.2023.
//

#include "../include/withDupWords.h"

Text getWithDupWords(Text text){
    Text dupText;
    dupText.sentences = malloc(sizeof(Sentence) * text.size);
    int dupTextSize = 0;
    for (int i = 0; i < text.size; i++) {
        Sentence tempSentence = text.sentences[i];
        Sentence newSentence;
        int newSentenceSize=0;
        int newSentenceBuffer=tempSentence.size+1;
        newSentence.chars = calloc((newSentenceBuffer*2),sizeof(wchar_t));
        int j =0;
        wchar_t* tokBuffer;
        wchar_t* dup = wcsdup(tempSentence.chars);
        wchar_t* word = wcstok(dup,L" ,.",&tokBuffer);
        while (j<tempSentence.size) {
            wchar_t tempChar = tempSentence.chars[j];

            if(tempChar!=' '&&tempChar!=','&&tempChar!='.'){
                int wordLength = wcslen(word);
                j+= wordLength;
                wchar_t * toCatWord = calloc((wordLength*2)+1, sizeof(wchar_t));

                wcscat(toCatWord, word);
                wcscat(toCatWord, L" ");
                wcscat(toCatWord, word);

                newSentenceSize+= wcslen(toCatWord);
                if (newSentenceBuffer<=newSentenceSize){
                    newSentenceBuffer+= newSentenceSize;
                    newSentence.chars = realloc(newSentence.chars,sizeof(wchar_t)*(newSentenceBuffer+1));
                }

                wcscat(newSentence.chars,toCatWord);
                word = wcstok(NULL,L" ,.",&tokBuffer);
            } else {
                newSentence.chars[newSentenceSize++]=tempChar;
                j++;
            }


        }
        free(tokBuffer);
        free(word);
        free(dup);
        free(text.sentences[i].chars);
        dupText.sentences[dupTextSize++]=newSentence;

    }

    dupText.size = dupTextSize;
    return dupText;
}