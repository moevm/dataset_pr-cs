//
// Created by rect on 17.11.2023.
//

#include "../include/inputOutput.h"

int getChoice(){
    int userChoice;
    wscanf(L"%d",&userChoice);
    return userChoice;
}

Text getText(){
    Text text;
    text.sentences = malloc(sizeof(Sentence));
    int textSize = 0, textBuffer=1;
    int nCounter=0;
    for(;;){
        Sentence tempSentence = getSentence(&nCounter);
        int equalSentence=0;
        for (int i = 0; i < textSize; ++i) {
            if(wcscasecmp(tempSentence.chars,text.sentences[i].chars)==0){
                equalSentence=1;
                break;
            }
        }
        if (nCounter==2) break;
        else nCounter=0;
        if(equalSentence==1) continue;
        wchar_t* tokBuffer;
        if(wcstok(wcsdup(tempSentence.chars),L" ,.",&tokBuffer)==NULL){
            continue;
        }
        text.sentences[textSize++]=tempSentence;
        text.size=textSize;
            if (textSize == textBuffer) {
                textBuffer *= 2;
                text.sentences = realloc(text.sentences, sizeof(Sentence) * textBuffer);
            }

    };
    if (text.sentences[0].chars==NULL){
        fwprintf(stderr, L"Error: Incorrect input.\n");
        exit(0);
    }
    return text;

}


Sentence getSentence(int *nCounter){
    Sentence sentence;
    sentence.chars = malloc(sizeof(wchar_t));
    int sentenceSize = 0;
    int sentenceBuffer = 1;
    wchar_t tempChar;
    int firstChar = 1;
    do{
        tempChar = getwchar();
        if (tempChar==L'\n') {
            (*nCounter)++;
            if((*nCounter)==2){
                break;
            }
            continue;
        }

        if (firstChar && iswspace(tempChar)) {
            continue;
        }

        firstChar=0;

        sentence.chars[sentenceSize++]=tempChar;
        if(sentenceSize==sentenceBuffer){
            sentenceBuffer *= 2;
            sentence.chars = realloc(sentence.chars, sizeof(wchar_t) * sentenceBuffer);
        }

    } while (tempChar!=L'.');
    sentence.chars[sentenceSize]=L'\0';
    sentence.size=sentenceSize;
    return sentence;
}

void printText(Text text){
    for (int i = 0; i < text.size; i++) {
        wprintf(L"%ls\n", text.sentences[i].chars);
    }
    printf("\n");
}
