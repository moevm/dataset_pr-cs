#include "sortByWordsLength.h"

int compareWords(const void* a, const void* b) {
    wchar_t* wordA = *((wchar_t**)a);
    wchar_t* wordB = *((wchar_t**)b);
    size_t lengthA = wcslen(wordA);
    size_t lengthB = wcslen(wordB);
    
    if (lengthA > lengthB) {
        return -1;
    } else if (lengthA < lengthB) {
        return 1;
    } else {
        return 0;
    }
}

void sortWords(Text* text) {
    for (int i = 0; i < text->size; i++) {
        Sentence* sentence = &(text->sentences[i]);
        wchar_t** words = (wchar_t**)malloc(sentence->wordCounter * sizeof(wchar_t*));
        wchar_t* word = wcstok(sentence->chars, L" .,", &(sentence->chars));
        wchar_t** punctuations = sentence->punctuation; 

        int wordIndex = 0;
        int punctuationIndex = 0;  
        while (word != NULL) {
            words[wordIndex] = word;
            word = wcstok(NULL, L" .,", &(sentence->chars));
            wordIndex++;
        }

        qsort(words, sentence->wordCounter, sizeof(wchar_t*), compareWords);

        wchar_t* newSentence = calloc((sentence->size + 2),sizeof(wchar_t));
        for (int j = 0; j < sentence->wordCounter; j++) {
            wcscat(newSentence, words[j]);
            wcscat(newSentence, punctuations[punctuationIndex]);
            punctuationIndex++;
            
        }

        sentence->chars = newSentence;

        free(words);
    }
}