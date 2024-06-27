#include <wchar.h>

#include "structures.h"

#define OPTION L"5.5"
#define NAME L"Kirill"
#define SURNAME L"Maltsev"

void printCourseInfoAndAuthor() {
    wprintf(L"Course work for option %ls, created by %ls %ls.\n", OPTION, NAME, SURNAME);
}

void printText(Text* text) {
    for (int i=0; i<text->sentencesNumber; i++) {
        wprintf(L"%ls\n", text->sentences[i].line);
    }
}