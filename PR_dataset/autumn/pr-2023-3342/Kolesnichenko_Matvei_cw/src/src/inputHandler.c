#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <wctype.h>

#include "structures.h"
#include "taskHandler.h"

int isEqual(const wchar_t *firstPointer, const wchar_t *secondPointer) {
    while (*firstPointer && towlower(*firstPointer) == towlower(*secondPointer)) {
        firstPointer++;
        secondPointer++;
    }
    return towlower(*firstPointer) - towlower(*secondPointer);
}

Word initializeWord(int buffer) {
    Word word;
    word.chars = malloc(sizeof(wchar_t) * buffer);
    checkMemory(word.chars, L"Memory allocation error - word.chars");
    word.followingChars = malloc(sizeof(wchar_t) * buffer);
    checkMemory(word.followingChars, L"Memory allocation error - word.followingChars");
    return word;
}

void endWord(Word* tempWord, int tempWordIndex, int followingCharsIndex) {
    tempWord->chars[tempWordIndex] = L'\0';
    tempWord->len = tempWordIndex - 1;
    tempWord->followingChars[followingCharsIndex] = L'\0';
    tempWord->followingLen = followingCharsIndex - 1;
}

Sentence initializeSentence(int buffer) {
    Sentence sentence;
    sentence.chars = malloc(sizeof(wchar_t) * buffer);
    checkMemory(sentence.chars, L"Memory allocation error - sentence.chars");
    sentence.words = malloc(sizeof(Word) * buffer);
    checkMemory(sentence.words, L"Memory allocation error - sentence.words");
    return sentence;
}

void endSentence(Sentence* tempSentence, int tempSentenceIndex, Word tempWord, int tempWordCounter) {
    tempSentence->chars[tempSentenceIndex] = L'\0';
    tempSentence->len = tempSentenceIndex - 1;
    tempSentence->words[tempWordCounter] = tempWord;
    tempSentence->wordsCounter = tempWordCounter;
}

void reallocateBuffers(Sentence* tempSentence, Word* tempWord, int* tempSentenceIndex, int* tempWordIndex,
                       int* followingCharsIndex, int* tempSentenceBuffer, int* tempWordBuffer,
                       int* followingCharsBuffer, int* tempWordCounter, int* tempWordCounterBuffer) {
    if (*tempSentenceIndex == *tempSentenceBuffer - 1) {
        *tempSentenceBuffer *= 2;
        tempSentence->chars = realloc(tempSentence->chars, sizeof(wchar_t) * (*tempSentenceBuffer));
        checkMemory(tempSentence->chars, L"Memory REallocation error - tempSentence.chars");
    }
    if (*tempWordIndex == *tempWordBuffer - 1) {
        *tempWordBuffer *= 2;
        tempWord->chars = realloc(tempWord->chars, sizeof(wchar_t) * (*tempWordBuffer));
        checkMemory(tempWord->chars, L"Memory REallocation error - tempWord.chars");
    }
    if (*followingCharsIndex == *followingCharsBuffer - 1) {
        *followingCharsBuffer *= 2;
        tempWord->followingChars = realloc(tempWord->followingChars, sizeof(wchar_t) * (*followingCharsBuffer));
        checkMemory(tempWord->followingChars, L"Memory REallocation error - tempWord.followingChars");
    }
    if (*tempWordCounter == *tempWordCounterBuffer - 1) {
        *tempWordCounterBuffer *= 2;
        tempSentence->words = realloc(tempSentence->words, sizeof(Word) * (*tempWordCounterBuffer));
        checkMemory(tempSentence->words, L"Memory REallocation error - tempSentence.words");
    }
}

Sentence getSentence(int* newLineCounter){
    wchar_t symbol; 
    Word tempWord;
    Sentence tempSentence;
    int tempSentenceIndex = 0, tempSentenceBuffer = 2;
    int tempWordCounter = 0, tempWordCounterBuffer = 2;
    int tempWordIndex = 0, tempWordBuffer = 2;
    int followingCharsIndex = 0, followingCharsBuffer = 2;
    int isEnded = 0, isFirst = 1;
    tempSentence = initializeSentence(tempSentenceBuffer);
    tempWord = initializeWord(tempWordBuffer);

    do{
        symbol = getwchar();
        if (symbol == L'\n'){
            (*newLineCounter)++;
            if (*newLineCounter == 2){
                break;
            }
        }
        else{
            *newLineCounter = 0;
        }

        reallocateBuffers(&tempSentence, &tempWord, &tempSentenceIndex, &tempWordIndex,
                      &followingCharsIndex, &tempSentenceBuffer, &tempWordBuffer,
                      &followingCharsBuffer, &tempWordCounter, &tempWordCounterBuffer);

        if (isFirst==1 && iswspace(symbol)){
            continue;
        }
        if (isFirst==1 && symbol == L'.'){
            continue;
        }
        isFirst = 0;
        if ((symbol!=L','&&symbol!=L'.')&&(symbol!=L' '&&symbol!=L'\t')&&(isEnded!=1)){
            tempWord.chars[tempWordIndex++] = symbol;
            tempSentence.chars[tempSentenceIndex++] = symbol;
        }
        else if((symbol!=L','&&symbol!=L'.')&&(symbol!=L' '&&symbol!=L'\t')&&(isEnded==1)){
            isEnded = 0;
            endWord(&tempWord, tempWordIndex, followingCharsIndex);
            tempSentence.words[tempWordCounter++] = tempWord;
            tempWordIndex = 0, followingCharsIndex = 0;
            tempWordBuffer = 2, followingCharsBuffer = 2;
            tempWord = initializeWord(tempWordBuffer);
            tempWord.chars[tempWordIndex++] = symbol;
            tempSentence.chars[tempSentenceIndex++] = symbol;
        } 
        else {
            isEnded = 1;
            tempWord.followingChars[followingCharsIndex++] = symbol;
            tempSentence.chars[tempSentenceIndex++] = symbol;
            
            if (symbol == L'.'){
                endWord(&tempWord, tempWordIndex, followingCharsIndex);
                endSentence(&tempSentence, tempSentenceIndex, tempWord, tempWordCounter);
                return tempSentence;
            }
        }
    } while(symbol != L'.');
}

Text getText(){
    int newLineCounter = 0;
    int textIndex = 0, textBuffSize = 2;

    Text rawText;
    rawText.sentences = malloc(textBuffSize*sizeof(Sentence));

    checkMemory(rawText.sentences, L"Memory allocation error - rawText.sentences");

    Sentence tempSentence;

    while(1){
        tempSentence = getSentence(&newLineCounter);
        if (newLineCounter == 2){
            break;
        }
        else{
            newLineCounter = 0;
        }
        if (textIndex == textBuffSize){
            textBuffSize *= 2;
            rawText.sentences = realloc(rawText.sentences, textBuffSize*sizeof(Sentence));
            checkMemory(rawText.sentences, L"Memory REallocation error - rawText.sentences");
        }
        rawText.sentences[textIndex++] = tempSentence;
    }
    textIndex--;

    int isUnique[textIndex+1];
    for (int i = 0; i <= textIndex; i ++){
        isUnique[i] = 1;
    }

    for(int i = 0; i <= textIndex; i++){
        for (int j = i+1; j <= textIndex; j++){
            if (!isEqual(rawText.sentences[i].chars, rawText.sentences[j].chars)){
                isUnique[j] = 0;
            }
        }
    }

    int uniqueIndex = 0;
    Text uniqueText;

    uniqueText.sentences = malloc((textIndex+1)*sizeof(Sentence));
    checkMemory(uniqueText.sentences, L"Memory allocation error - uniqueText.sentences");

    for (int i = 0; i <= textIndex; i++){
        if (isUnique[i] == 1){
            uniqueText.sentences[uniqueIndex++] = rawText.sentences[i];
        }
    }
    uniqueText.sentenceCounter = uniqueIndex-1;
    return uniqueText;
}

int getTask(){
    int choice;
    wscanf(L"%d", &choice);
    return choice;
}
