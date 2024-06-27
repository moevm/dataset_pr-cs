#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

#include "structures.h"

void getTestType(int* testType) {
    wscanf(L"%d", testType);
}

wchar_t* getInput(int* sentencesNumber, int testType) {
    
    int textSize = 0;
    int capacity = 0;
    wchar_t* text = NULL;

    int newLineCount = 0;
    
    wchar_t ch = 0;
    if (testType != 9) {
        ch = getwchar(); // skipping the first '\n'
    }

    while (newLineCount < 2) {
        ch = getwchar();
        if (ch == '\n') newLineCount++;
        else newLineCount = 0;
        
        if (textSize + 1 >= capacity) {
            capacity = (capacity == 0) ? 2 : capacity * 2;
            text = (wchar_t*) realloc(text, capacity * sizeof(wchar_t));
        }
        
        if (ch == L'.') {
            (*sentencesNumber)++;
        }

        text[textSize] = ch;
        textSize++;
    }
    text[textSize-2] = L'\0';
    return text;
}

void splitText(Text* text, wchar_t* input) {
    text->sentences = (Sentence*) malloc(text->sentencesNumber * sizeof(Sentence));
    wchar_t* delim = L".";
    wchar_t* token;
    wchar_t* ptr;

    token = wcstok(input, delim, &ptr);
    int i = 0;
    while (token != NULL) {
        while (iswspace(*token)) {
    		token++;
		}
        text->sentences[i].line = (wchar_t*) calloc(wcslen(token)+2, sizeof(wchar_t));
        wcscpy(text->sentences[i].line, token);
        text->sentences[i].line[wcslen(token)] = L'.';
        text->sentences[i].sentenceSize = wcslen(text->sentences[i].line);
        i++;
        token = wcstok(NULL, delim, &ptr);
    }
}