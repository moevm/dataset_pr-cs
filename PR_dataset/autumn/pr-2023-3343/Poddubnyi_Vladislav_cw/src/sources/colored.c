//
// Created by rect on 17.11.2023.
//

#include "../include/colored.h"

Text getColored(Text text) {
    Text coloredText;
    coloredText.sentences = malloc(sizeof(Sentence)*text.size);
    int coloredTextSize = 0;
    for (int i = 0; i < text.size; i++) {
        Sentence tempSentence = text.sentences[i];
        int newSentenceSize=0;
        int j =0;
        wchar_t* tokBuffer;
        wchar_t* dup = wcsdup(tempSentence.chars);
        wchar_t* word = wcstok(dup,L" ,.",&tokBuffer);
        int newSentenceBuffer=1;
        coloredText.sentences[coloredTextSize].chars = calloc(newSentenceBuffer,sizeof(wchar_t));
        while (j<tempSentence.size) {
            wchar_t tempChar = tempSentence.chars[j];

            if(tempChar!=' '&&tempChar!=','&&tempChar!='.'){
                int wordLength = wcslen(word);
                j+= wordLength;
                int color = wordLength%4;
                wchar_t * toCatWord = calloc(wordLength+10, sizeof(wchar_t));


                switch (color) {
                    case 0:
                        wcscat(toCatWord, RED);
                        break;
                    case 1:
                        wcscat(toCatWord, BLUE);
                        break;
                    case 2:
                        wcscat(toCatWord, GREEN);
                        break;
                    case 3:
                        wcscat(toCatWord, YELLOW);
                        break;
                }
                wcscat(toCatWord, word);
                wcscat(toCatWord, DEFAULT);

                newSentenceSize+= wcslen(toCatWord);
                if (newSentenceBuffer<=newSentenceSize){
                    newSentenceBuffer= newSentenceSize+1;
                    coloredText.sentences[coloredTextSize].chars = realloc(coloredText.sentences[coloredTextSize].chars,sizeof(wchar_t)*(newSentenceBuffer));
                }

                wcscat(coloredText.sentences[coloredTextSize].chars,toCatWord);
                coloredText.sentences[coloredTextSize].chars[newSentenceSize]='\0';
                free(toCatWord);
                word = wcstok(NULL,L" ,.",&tokBuffer);
            } else {
                newSentenceSize++;
                if (newSentenceBuffer<=newSentenceSize){
                    newSentenceBuffer = newSentenceSize+1;
                    coloredText.sentences[coloredTextSize].chars = realloc(coloredText.sentences[coloredTextSize].chars,sizeof(wchar_t)*(newSentenceBuffer));
                }
                coloredText.sentences[coloredTextSize].chars[newSentenceSize-1]=tempChar;
                coloredText.sentences[coloredTextSize].chars[newSentenceSize]='\0';
                j++;
            }

        }
        free(tokBuffer);
        free(word);
        free(dup);
        free(text.sentences[i].chars);
        coloredTextSize++;

    }

    coloredText.size = text.size;

    return coloredText;
}

