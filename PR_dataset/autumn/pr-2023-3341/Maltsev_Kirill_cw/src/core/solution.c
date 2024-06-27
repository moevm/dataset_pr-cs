#include <stdlib.h>
#include <wchar.h>

#include "structures.h"
#include "allocator.h"
#include "input.h"
#include "removeDuplicates.h"
#include "error.h"

void getStr(wchar_t* str) {
    wchar_t ch = getwchar();
    ch = 0;
    int i = 0;
    while (ch != L'\n') {
        ch = getwchar();
        str[i] = ch;
        i++;
    }
    str[i-1] = '\0';
}

void solution(int testType) {
    wchar_t* str = (wchar_t*) calloc(10000, sizeof(wchar_t));

    if (textWillBeEntered(testType)) {

        if (testType == 9) {
            getStr(str);
        }

        Text* text = createText();
        wchar_t* input = getInput(&(text->sentencesNumber), testType);
        
        if (input[wcslen(input)-1] != '.') {
            throwTextEndError();
            return;
        }

        splitText(text, input);
        
        removeDuplicates(text);
        
        allocator(text, testType, str);
        free(text);
    }
}