#include "../include/text_processing.h"

int strCaseCmp(const char *s1, const char *s2) {
    int c1, c2;
    while (*s1 && *s2){
        c1 = toupper(*s1);
        c2 = toupper(*s2);
        if (c1 != c2){
            return c1 - c2;
        }
        s1++;
        s2++;
    }
    if(*s1){
        return 1;
    }
    if(*s2){
        return -1;
    }
    return 0;
}

int countWordInSentence(Word word, Sentence sentence){
    int counter = 0;
    Sentence sentenceCopy;
    sentenceCopy.chars = (char *)malloc(sizeof(char) * (sentence.size + 1));
    strcpy(sentenceCopy.chars, sentence.chars);
    size_t numberOfWords = 0, capacity = 1;
    Word *words = (Word *)malloc(sizeof(Word) * capacity);
    Word curWord;
    curWord.letters = strtok(sentenceCopy.chars, WORD_SPLITTERS);
    while(curWord.letters != NULL){
        words[numberOfWords].letters = (char *)malloc(sizeof(char) * (strlen(curWord.letters) + 1));
        words[numberOfWords].size = strlen(curWord.letters);
        words[numberOfWords] = curWord;
        words[numberOfWords++].letters[strlen(curWord.letters)] = '\0';
        if(numberOfWords == capacity){
            capacity += 1;
            words = (Word *)realloc(words, sizeof(Word) * capacity);
        }
        curWord.letters = strtok(NULL, WORD_SPLITTERS);
    }
    for(size_t i = 0; i < numberOfWords; i++)
        if(strCaseCmp(word.letters, words[i].letters) == 0) counter++;
    return counter;
}

int compare(const void *a, const void *b){
    Sentence *sentenceA = (Sentence *)a;
    Sentence *sentenceB = (Sentence *)b;
    int uppercaseLettersInSentenceA = 0;
    int uppercaseLettersInSentenceB = 0;
    for(size_t i = 0; i < sentenceA->size; i++){
        if(isupper(sentenceA->chars[i])){
            uppercaseLettersInSentenceA++;
        }
    }
    for(size_t i = 0; i < sentenceB->size; i++){
        if(isupper(sentenceB->chars[i])){
            uppercaseLettersInSentenceB++;
        }
    }
    return uppercaseLettersInSentenceB - uppercaseLettersInSentenceA;
}

void replaceSymbolWithSubstring(Sentence *sentence, char symbol, char *substring){
    char *symbolPointer = strchr(sentence->chars, symbol);
    while(symbolPointer){
        size_t index = symbolPointer - sentence->chars;
        sentence->size += (strlen(substring) - 1);
        sentence->chars = (char *)realloc(sentence->chars, sizeof(char) * (sentence->size + 1));
        memmove(sentence->chars + index + strlen(substring), sentence->chars + index + 1, sentence->size - index - strlen(substring) + 1);
        memmove(sentence->chars + index, substring, strlen(substring));
        symbolPointer = strchr(sentence->chars + index + 1, symbol);
    }
}

void initialMandarotyProcessing(){
    Text text = getText();
    printText(text);
    freeText(text);
}

void outputOnlyDigitsSentences(){
    Text initialText = getText();
    size_t resultedTextSize = 0, capacity = 1;
    Text resultedText;
    resultedText.sentences = (Sentence *)malloc(sizeof(Sentence) * capacity);
    for(size_t i = 0; i < initialText.size; i++){
        int onlyDigits = 1;
        for(size_t j = 0; j < initialText.sentences[i].size - 1; j++){
            if((!isdigit(initialText.sentences[i].chars[j])) && (!isspace(initialText.sentences[i].chars[j]))){
                onlyDigits = 0;
                break;
            }
        }
        if(onlyDigits == 1){
            if(resultedTextSize == capacity){
                capacity += 1;
                resultedText.sentences = (Sentence *)realloc(resultedText.sentences, (sizeof(Sentence) * capacity));
            }

            resultedText.sentences[resultedTextSize].chars = (char *)malloc(sizeof(char) * (initialText.sentences[i].size + 1));
            strcpy(resultedText.sentences[resultedTextSize++].chars, initialText.sentences[i].chars);
        }
    }
    resultedText.size = resultedTextSize;
    printText(resultedText);
    freeText(initialText);
    freeText(resultedText);
}

void sortSentencesByTheNumberOfUppercaseLettersInIt(){
    Text text = getText();
    qsort(text.sentences, text.size, sizeof(Sentence), compare);
    printText(text);
    freeText(text);
}

void deleteSentenceWithTheInputtedWord(){
    getchar();
    Word inputtedWord = getWord();
    Text initialText = getText();
    size_t resultedTextSize = 0, capacity = 1;
    Text resultedText;
    resultedText.sentences = (Sentence *)malloc(sizeof(Sentence) * capacity);
    for(size_t i = 0; i < initialText.size; i++){
        if(countWordInSentence(inputtedWord, initialText.sentences[i]) < 2){
            if(resultedTextSize == capacity){
                capacity += 1;
                resultedText.sentences = (Sentence *)realloc(resultedText.sentences, sizeof(Sentence) * capacity);
            }
            resultedText.sentences[resultedTextSize].chars = (char *)malloc(sizeof(char) * (initialText.sentences[i].size + 1));
            strcpy(resultedText.sentences[resultedTextSize++].chars, initialText.sentences[i].chars);
        }
    }
    resultedText.size = resultedTextSize;
    printText(resultedText);
    free(inputtedWord.letters);
    freeText(initialText);
    freeText(resultedText);
}

void replaceDigitsInSentences(){
    Text text = getText();
    for(size_t i = 0; i < text.size; i++){
        replaceSymbolWithSubstring(&text.sentences[i], '0', "Zero");
        replaceSymbolWithSubstring(&text.sentences[i], '1', "One");
        replaceSymbolWithSubstring(&text.sentences[i], '2', "Two");
        replaceSymbolWithSubstring(&text.sentences[i], '3', "Three");
        replaceSymbolWithSubstring(&text.sentences[i], '4', "Four");
        replaceSymbolWithSubstring(&text.sentences[i], '5', "Five");
        replaceSymbolWithSubstring(&text.sentences[i], '6', "Six");
        replaceSymbolWithSubstring(&text.sentences[i], '7', "Seven");
        replaceSymbolWithSubstring(&text.sentences[i], '8', "Eight");
        replaceSymbolWithSubstring(&text.sentences[i], '9', "Nine");
    }
    printText(text);
    freeText(text);
}

void repeatSentences(){
    int amount = getDigit();
    Text text = getText();
    Text newText;
    newText.sentences = (Sentence *)malloc(sizeof(Sentence) * text.size);
    newText.size = text.size;
    for(size_t i = 0; i < newText.size; i++){
        newText.sentences[i].chars = (char *)malloc(sizeof(char) * (text.sentences[i].size * amount + 1));
        if(amount == 1){
            strcpy(newText.sentences[i].chars, text.sentences[i].chars);
        }else{
            int index = 0;
            for(int j = 0; j < amount - 1; j++){
                strncpy(newText.sentences[i].chars + index, text.sentences[i].chars, text.sentences[i].size - 1);
                index += (text.sentences[i].size - 1);
                newText.sentences[i].chars[index++] = ' ';
            }
            strcpy(newText.sentences[i].chars + index, text.sentences[i].chars);
            index = 0;
        }
        newText.sentences[i].size = text.sentences[i].size * amount;
    }
    printText(newText);
    freeText(text);
    freeText(newText);
}
