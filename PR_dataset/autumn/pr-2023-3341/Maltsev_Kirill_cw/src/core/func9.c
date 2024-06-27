#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

#include "structures.h"
#include "bst.h"

void addWords(Bst* bst, wchar_t* line) {
    wchar_t* delim = L"., \f\n\r\text\v";
    wchar_t* token;
    wchar_t* ptr;

    token = wcstok(line, delim, &ptr);
    while (token != NULL) {
        while (iswspace(*token)) {
    		token++;
		}
        insert(bst, token);
        token = wcstok(NULL, delim, &ptr);        
    }
}

int shouldBeOutputed(Bst* bst, Sentence* sentence) {
    wchar_t* cpy = (wchar_t*) calloc(wcslen(sentence->line)+1, sizeof(wchar_t));
    wcscpy(cpy, sentence->line);

    for (int j=0; j<wcslen(cpy); j++) {
        cpy[j] = towupper(cpy[j]);
    }

    wchar_t* delim = L"., \f\n\r\t\v";
    wchar_t* token;
    wchar_t* ptr;

    token = wcstok(cpy, delim, &ptr);
    while (token != NULL) {
        while (iswspace(*token)) {
    		token++;
		}
        if ((find(bst, token)) == 0) return 0;
        token = wcstok(NULL, delim, &ptr);     
    }
    return 1;
}

void func9(wchar_t* str, Text* text) {
    for (int j=0; j<wcslen(str); j++) {
        str[j] = towupper(str[j]);
    }

    Bst* bst = createBst();
    addWords(bst, str);
    for (int i=0; i<text->sentencesNumber; i++) {
        if (shouldBeOutputed(bst, &text->sentences[i])) {
            wprintf(L"%ls\n", text->sentences[i].line);
        }
    }

}