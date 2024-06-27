#include "../include/input.h"
#define SIZE_STEP 20

Sentence getSentence(int* count, int* task) {
    Sentence sentence;
    int size = 0;
    *count = 0;
    int limit = SIZE_STEP;
    sentence.words = malloc(sizeof(wchar_t)*SIZE_STEP);
    wchar_t letter;
    int emptySpaces = 1;
    int quit = 0;
    int once = 0;
    if (*task == 9)
        once = 1;
    while((letter = getwchar()) != L'.') {
        if (letter == L'\n') {
            *count = *count + 1;
            if (*task == 9 && once) {
                once = 0;
                continue;
            }
            if (*task == 9) {
                quit = 1;
                break;
                *count = 0;
            }
            if (*count == 2) {
                if (size > 0 && sentence.words[size-1] != L'.')
                    quit = 1;
                break;
            }
            continue;
        }
        *count = 0;
 
        if (emptySpaces && (letter == L' ' || letter == L',' || letter == L'\t')) {
            continue;
        }
 
        emptySpaces = 0;
        if (size >= limit - 1) {
            limit += SIZE_STEP;
            sentence.words = realloc(sentence.words,sizeof(wchar_t)*limit);
        }
        sentence.words[size++] = letter;
    }
 
    sentence.words = realloc(sentence.words,sizeof(wchar_t)*(size+2));
    if (quit)
        sentence.words[size++] = '.';
    else 
        sentence.words[size++] = letter;
    sentence.words[size] = L'\0';
    sentence.size = size;
 
    return sentence;
}
 
Text getText(int task) {
    Text text;
    text.sentences = malloc(sizeof(Sentence));
    int currentSize = 0;
    int maxSize = 1;
    int count = 0;
    int sameSentence = 0;
    int emptySentence = 0;
    text.size = 0;
    int state = 1;
    while (state) {
        Sentence new = getSentence(&count, &task);
        task = 0;
        if (count == 2)
            state = 0;
        else
            count = 0;
 
        for (int i = 0; i < text.size; ++i) {
            if (wcscasecmp(new.words,text.sentences[i].words) == 0) {
                sameSentence = 1;
                break;
            }
        }
        if (sameSentence) {
            sameSentence = 0;
            continue;
        }
 
        if (new.size == 1) {
            emptySentence = 1;
            continue;
        }
        text.sentences[currentSize++] = new;
        text.size = currentSize;
        if (currentSize == maxSize) {
            maxSize += SIZE_STEP;
            text.sentences = realloc(text.sentences, sizeof(Sentence)*maxSize);
        }
    }

    if (text.size == 0 && emptySentence) {
        wprintf(L"Error: incorrect text input, sentences not found.\n");
        exit(0);
    }
    
    return text;
}