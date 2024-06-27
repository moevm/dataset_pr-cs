//
// Created by rect on 19.11.2023.
//

#include "../include/withoutNums.h"

Text getWithoutNums(Text text){
    Text newText;
    int newTextBuffer = 1;
    int newTextSize=0;
    newText.sentences = malloc(sizeof(Sentence)*newTextBuffer);
    for (int i=0;i<text.size;i++){
        Sentence tempSentence = text.sentences[i];
        Sentence newSentence;
        int newSentenceSize=0;
        int newSentenceBuffer=tempSentence.size+1;
        newSentence.chars = calloc(newSentenceBuffer,sizeof(wchar_t));
        wchar_t* tokBuffer;
        wchar_t * word = wcstok(wcsdup(tempSentence.chars),L" ",&tokBuffer);
        int isNum = 1;
        int j=0;
        while (j<tempSentence.size) {
            wchar_t tempChar = tempSentence.chars[j];
            if(tempChar!=L' '&&tempChar!=L','&&tempChar!=L'.'){
            if(word==NULL) break;
            for(int k=0;k< wcslen(word);k++){
                if(!iswdigit(word[k])){
                    isNum=0;
                    break;
                }
            }

            int wordLength = wcslen(word);
            if (!isNum){
                newSentenceSize+= wordLength;
                j+= wordLength;
                if (newSentenceBuffer<=newSentenceSize){
                    newSentenceBuffer = newSentenceSize+1;
                    newSentence.chars = realloc(newSentence.chars,sizeof(wchar_t)*newSentenceBuffer);
                }

                wcscat(newSentence.chars,word);
            } else {
                j+=wordLength;
            }
            word = wcstok(NULL,L" ",&tokBuffer);
            isNum=1;
        } else {
                newSentenceSize++;
                if (newSentenceBuffer<=newSentenceSize){
                    newSentenceBuffer = newSentenceSize+1;
                    newSentence.chars = realloc(newSentence.chars,sizeof(wchar_t)*(newSentenceBuffer));
                }
                newSentence.chars[newSentenceSize-1]=tempChar;
                newSentence.chars[newSentenceSize]='\0';
                j++;
            }

        }
        newTextSize++;
        if (newTextBuffer<=newTextSize){
            newTextBuffer = newTextSize+1;
            newText.sentences = realloc(newText.sentences,sizeof(Sentence)*newTextBuffer);
        }
        newText.sentences[newTextSize-1]=newSentence;
    }
    newText.size = newTextSize;
    return newText;
}
