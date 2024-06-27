#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>
#include <wctype.h>
#include <string.h>

#include "structures.h"

int wcscasecmp(const wchar_t *s1, const wchar_t *s2);

void addSentence(struct Text *text, wchar_t *sentence, int len) {

    int i = 0;
    while ((sentence[i] == L' ' || sentence[i] == L'\n') && i < len) {
        i++;
    }
    if (i > 0) {
        int j;
        for (j = 0; j < len - i; j++) {
            sentence[j] = sentence[j + i];
        }
        sentence[j] = L'\0';
    }
    

    text->sentences = (struct Sentence **)realloc(text->sentences, (text->len + 1) * sizeof(struct Sentence *)); //Память на указатели
    text->sentences[text->len] = (struct Sentence *)malloc(sizeof(struct Sentence)); //Выделяем память под предложение в структуре текст
    text->sentences[text->len]->sentence = (wchar_t *)malloc((len + 1) * sizeof(wchar_t));//В самой структуре предложения память
    wcscpy(text->sentences[text->len]->sentence, sentence);
    text->sentences[text->len]->len = len;
    text->len++;
    for (int i = 0; i < text->len - 1; i++) {
        if (wcscasecmp(text->sentences[i]->sentence, sentence) == 0) {
            free(text->sentences[text->len - 1]->sentence);
            free(text->sentences[text->len - 1]);
            text->len--;
            return;
        }
    }
}

struct Text MakingStruct(){
    struct Text text;
    text.sentences = NULL;
    text.len = 0;
    text.dotChecker = 0;

    wchar_t *input = (wchar_t *)malloc(100 * sizeof(wchar_t));
    wchar_t *buffer = (wchar_t *)malloc(100 * sizeof(wchar_t));
    int inputSize = 100;
    int bufferSize = 100;
    int len = 0;
    int newLineCount = 0;

    while (1) {    
        fgetws(buffer, bufferSize, stdin);
        if(newLineCount){
            if(buffer[0] == L'\n'){
                break;
            }
            newLineCount = 0;
        }
        if (buffer[wcslen(buffer)-1] == L'\n') {
            newLineCount++;
        } 
        if (len + wcslen(buffer) >= inputSize) {
            inputSize *= 2;
            input = (wchar_t *)realloc(input, inputSize * sizeof(wchar_t));
        }
        wcscat(input, buffer);
        len += wcslen(buffer);
    }

    if(input[wcslen(input) - 2] == L'.'){
        text.dotChecker = 1;
        input[wcslen(input) - 2] = L'\0';
    }

    wchar_t *sentence = wcstok(input, L".", &input);
    while (sentence != NULL) {
        if (wcslen(sentence) == 1){
            break;
        }
        addSentence(&text, sentence, wcslen(sentence));
        sentence = wcstok(NULL, L".", &input);
    }
    free(input);
    free(buffer);
    return text;
}
