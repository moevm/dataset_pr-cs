#include "../include/input.h"

int getCommand(){
    int command;
    scanf("%d", &command);
    return command;
}

int getDigit(){
    int digit;
    scanf("%d", &digit);
    return digit;
}

Word getWord(){
    size_t wordSize = 0, capacity = 1;
    Word word;
    word.letters = (char *)malloc(sizeof(char) * capacity);
    char curLetter;
    while((curLetter = getchar()) != '\n'){
        if(wordSize == capacity){
            capacity += 1;
            word.letters = (char * )realloc(word.letters, sizeof(char) * capacity);
        }
        word.letters[wordSize++] = curLetter;
    }
    word.letters[wordSize] = '\0';
    word.size = wordSize;
    return word;
}

Sentence getSentence(int *nCounter){
    size_t sentenceSize = 0, capacity = 1;
    Sentence sentence;
    sentence.chars = (char *)malloc(sizeof(char) * capacity);
    char curChar;
    while((curChar = getchar()) != SENTENCE_SPLITTER){
        if(curChar == '\n'){
            (*nCounter)++;
            if(*nCounter == 2) break;
            continue;
        }
        *nCounter = 0;
        if(isspace(curChar) && sentenceSize == 0) continue;
        if(sentenceSize == capacity){
            capacity += 1;
            sentence.chars = (char *)realloc(sentence.chars, sizeof(char) * capacity);
        }
        sentence.chars[sentenceSize++] = curChar;
    }
    sentence.chars = (char *)realloc(sentence.chars, sizeof(char) * (sentenceSize + 2));
    sentence.chars[sentenceSize++] = SENTENCE_SPLITTER;
    sentence.chars[sentenceSize] = '\0';
    sentence.size = sentenceSize;
    return sentence;
}


Text getText(){
    int nCounter = 0;
    size_t textSize = 0, capacity = 1;
    Text text;
    text.sentences = (Sentence *)malloc(sizeof(Sentence) * capacity);
    for(;;){
        Sentence curSentence = getSentence(&nCounter);
        int newSentence = 1;
        for(size_t i = 0; i < textSize; i++){
            if(!strCaseCmp(text.sentences[i].chars, curSentence.chars)){
                newSentence = 0;
                break;
            }
        }
        if(nCounter == 2) break;
        else nCounter = 0;
        if(newSentence == 0) continue;
        if(textSize == capacity){
            capacity += 1;
            text.sentences = (Sentence *)realloc(text.sentences, sizeof(Sentence) * capacity);
        }
        text.sentences[textSize++] = curSentence;
    }
    text.size = textSize;
    checkMemoryAllocation(text.sentences[0].chars);
    return text;
}
