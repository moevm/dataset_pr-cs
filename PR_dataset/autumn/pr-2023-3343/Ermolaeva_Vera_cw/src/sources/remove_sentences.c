#include <stdlib.h>
#include <wchar.h>
#include <string.h>
#include <ctype.h>
#include "../include/struct.h"

wchar_t* getLastWord(Sentence* sentence) {
    wchar_t* words[sentence->size];
    int size = 0;

    wchar_t* state;
    wchar_t* token = wcstok(wcsdup(sentence->sentence), L" ,", &state);

    while (token != NULL) {
        words[size++] = token;
        token = wcstok(NULL, L" ,.?", &state);
    }

    return words[size-1];
}

int countConsonants(wchar_t* last_word) {
    wchar_t* vowels = L"aeiouауоиэыяюеё";

    int index = 0;
    int count_consonants = 1;

    for(int i=0; i<wcslen(last_word); i++) {
        if (wcschr(vowels, tolower(last_word[i])) == 0) {
            if (i-index == 1 && wcschr(vowels, tolower(last_word[index])) == 0)
                count_consonants++;
            index = i;
        } else {
            if (count_consonants == 3)
                break;
            else 
                count_consonants = 1;
        }
    }

    return count_consonants;
}

void removeSentences(Text* text) {
    int count_consonants;

    for (int i=0; i<text->real_size; i++) {
        count_consonants = countConsonants(getLastWord(&text->sentences[i]));
        
        if (count_consonants == 3) {                    
            memmove(&text->sentences[i], &text->sentences[i+1], sizeof(Sentence)*(text->real_size-i));
            text->real_size--;

            free(text->sentences[text->real_size].sentence);
            i = 0;
        }
    }
}