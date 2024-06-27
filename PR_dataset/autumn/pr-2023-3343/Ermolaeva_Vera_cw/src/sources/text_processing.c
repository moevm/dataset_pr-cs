#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../include/struct.h"

#define BLOCK 100;

Text createText() {
    Text text;
    text.size = BLOCK;
    text.real_size = 0;

    text.sentences = malloc(text.size * sizeof(Sentence));
    return text;
}

void addSentence(Text* text, Sentence sentence) {
    if(text->real_size == text->size) {
        text->size += BLOCK;
        text->sentences = realloc(text->sentences, text->size * sizeof(Sentence));
    }
    text->sentences[text->real_size++] = sentence;
}

Sentence readSentence() {
    Sentence sentence;
    sentence.size = BLOCK;
    sentence.sentence = (wchar_t*) malloc((sentence.size + 1) * sizeof(wchar_t));

    int i;
    wchar_t ch;
    wchar_t prev_char;

    for(i=0; i <= sentence.size; i++) {
        ch = getwchar();
        sentence.sentence[i] = ch;

        if (wcscmp(sentence.sentence, L"\n\n") == 0) {
            break;
        }

        if (sentence.sentence[i] == L' ' && i == 0) 
            i--;

        if (wcschr(L".?!", ch)) {
            i++;
            sentence.sentence[i] = L'\0';
            break;
        }

        if(i == sentence.size) {
            sentence.size += BLOCK;
            sentence.sentence = (wchar_t*) realloc(sentence.sentence, (sentence.size + 1) * sizeof(wchar_t));
        }

        prev_char = ch;
    }

    return sentence;
}

void readText(Text* text) {
    Sentence sentence;

    for(int i=0; i<=text->real_size; i++) {
        sentence = readSentence();

        if(wcscmp(sentence.sentence, L"\n\n") == 0)
            break;

        // wprintf(L"%ls\n", sentence.sentence);

        addSentence(&(*text), sentence);
    }
}

void clearText(Text* text) {
    wchar_t* sentence1;
    wchar_t* sentence2;

    for(int i=0; i<text->real_size; i++) {
        sentence1 = text->sentences[i].sentence;
        
        for(int j=i+1; j<text->real_size; j++) {
            int len = -1;
            int count = 0;
            sentence2 = text->sentences[j].sentence;

            if (wcslen(sentence1) == wcslen(sentence2)) {
                len = wcslen(sentence1);
                for(int k=0; k<len; k++) {
                    if (tolower(sentence1[k]) == tolower(sentence2[k]))
                        count++;
                }
            }

            if (count == len) {
                memmove(&text->sentences[i], &text->sentences[i+1], sizeof(Sentence)*(text->real_size-i));
                text->real_size--;

                free(text->sentences[text->real_size].sentence);
            }
        }
    }
}

void printText(Text* text) {
    for(int i=0; i<text->real_size; i++) {
        if (text->sentences[i].sentence[0] == L'\n')
            memmove(text->sentences[i].sentence, &text->sentences[i].sentence[1], sizeof(wchar_t)*wcslen(text->sentences[i].sentence));
        wprintf(L"%ls\n", text->sentences[i]);
    }
}

void freeText(Text* text) {
    for(int i=0; i<text->real_size; i++)
        free(text->sentences[i].sentence);

    free(text->sentences);
}