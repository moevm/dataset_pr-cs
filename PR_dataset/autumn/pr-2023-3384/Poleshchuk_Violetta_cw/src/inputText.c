#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include "header_files/inputText.h"
#include "header_files/structures.h"


Sentence readSentence(int* counterN){
    int contentVolume = 1;
    int contentLen = 0;
    Sentence sentence;
    wchar_t* content = (wchar_t*)malloc(sizeof(wchar_t)*contentVolume);
    if (content == NULL) {
                printf("Error: Memory allocation error for content in readSentence\n");
            }
    wchar_t symbol;
    do{
        symbol = getwchar();
        if (symbol == L'\n'){
            (*counterN)++;
        }
        
        if ((*counterN) == 2){
            if ( contentLen > 1 && content[contentLen-1] != '.'){
                content[contentLen-1] = '.';
            }
            break;
        }

        if (symbol == '\n' && contentLen == 0){
            continue;
        }

        if (symbol != '\n' && (*counterN) == 1){
            (*counterN) = 0;
            if (contentLen > 0) content[contentLen-1] = ' ';
        }
        
        if (symbol == ' ' && contentLen > 0 && content[contentLen-1] == ' '){
            continue;
        }

        if (!(symbol == ' ' && contentLen == 0 )){
            content[contentLen++] = symbol;
            if (contentLen >= contentVolume){
                contentVolume *= 2;
                content = (wchar_t*)realloc(content, sizeof(wchar_t)*contentVolume);
            }
        }
    }while(symbol != L'.');
    content = (wchar_t*)realloc(content, sizeof(wchar_t)*(contentLen+1));
    content[contentLen] = L'\0';
    sentence.content = content;
    sentence.len = contentLen;

    int wordsVolume = 1;
    int currWord = 0;
    sentence.words = malloc(sizeof(Word)*wordsVolume);
    if (sentence.words == NULL) {
                printf("Error: Memory allocation error for words\n");
        }
    
    for (int i = 0; i < sentence.len; i++){
        if (currWord >= wordsVolume){
                    wordsVolume += 2;
                    sentence.words = realloc(sentence.words, sizeof(Word)*wordsVolume);
                }
        if(content[i] != ',' && content[i] != ' '){
            int currSymbol = 0;
            int volumeSymbol = 1;
            sentence.words[currWord].symbols = malloc(sizeof(wchar_t)*volumeSymbol);
            if (sentence.words == NULL) {
                printf("Error: Memory allocation error for word's symbols\n");
            }
            sentence.words[currWord].symbols[currSymbol++] = content[i];
            i++;
            while(!iswpunct(content[i]) && i<sentence.len && content[i] != ' '){
                if (currSymbol >= volumeSymbol){
                    volumeSymbol *= 2;
                    sentence.words[currWord].symbols = realloc(sentence.words[currWord].symbols, sizeof(wchar_t)*volumeSymbol);
                }
                sentence.words[currWord].symbols[currSymbol++] = content[i];
                i++;
            }
            sentence.words[currWord].symbols = realloc(sentence.words[currWord].symbols, sizeof(wchar_t)*(currSymbol+1));
            sentence.words[currWord].symbols[currSymbol] = L'\0';
            
            sentence.words[currWord].len = currSymbol;

        }
        if (content[i] == ',' || content[i] == ' ' || content[i] == '.'){
            int currPunctuation = 0;
            int volumePunctuation = 1;
            sentence.words[currWord].punctuation = malloc(sizeof(wchar_t)*(volumePunctuation+1));
            sentence.words[currWord].punctuation[currPunctuation++] = content[i];
            i++;
            while ((content[i] == ',' || content[i] == ' ' || content[i] == '.') && i<sentence.len){
                if (currPunctuation >= volumePunctuation){
                    volumePunctuation *= 2;
                    sentence.words[currWord].punctuation = realloc(sentence.words[currWord].punctuation, sizeof(wchar_t)*volumePunctuation);
                }
                sentence.words[currWord].punctuation[currPunctuation++] = content[i];
                i++;
            }
            sentence.words[currWord].punctuation = realloc(sentence.words[currWord].punctuation, sizeof(wchar_t)*(currPunctuation+1));
            sentence.words[currWord].punctuation[currPunctuation] = L'\0';
            
            i--;
            currWord++;
            }
        } 
    
    sentence.counterWords = currWord;
    return sentence;
}

Text madeText(){
    Text text;
    int volumeText = 1;
    int numSentence = 0;
    int countSymbols = 0;
    text.sentences = (Sentence*)malloc(sizeof(Sentence)*volumeText);
    if (text.sentences == NULL) {
                printf("Error: Memory allocation error for sentence\n");
    }
    int countWords = 0;
    Sentence cursSentence;
    int counterN = 0;
    do{
        cursSentence = readSentence(&counterN);
        int equal = 0;
        if(counterN == 2 && cursSentence.len < 2){
            break;
        }else{
            for (int index = 0; index < numSentence; index++){
                if( wcscasecmp(text.sentences[index].content, cursSentence.content) == 0){
                    equal = 1;
                }

            }
            if (cursSentence.len == 1){
                continue;
            }

            if (equal == 0){
                text.sentences[numSentence++] = cursSentence;
                countWords += cursSentence.counterWords;
                countSymbols += cursSentence.len;
                if (volumeText <= numSentence){
                    volumeText *= 2;
                    text.sentences = (Sentence*)realloc(text.sentences, sizeof(Sentence)*volumeText);
                }
            }
        }
    }while(counterN != 2);
    text.sentences = (Sentence*)realloc(text.sentences, sizeof(Sentence)*(numSentence));
    text.countSentences = numSentence;
    text.countWords = countWords;
    text.countSymbols = countSymbols;
    return text;
}

void output(Text text){
    for (int i = 0; i < text.countSentences; i++){
                wprintf(L"%ls\n", text.sentences[i].content);
    }
}