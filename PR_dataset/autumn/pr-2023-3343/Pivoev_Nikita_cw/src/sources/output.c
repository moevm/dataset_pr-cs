#include "../include/output.h"

void printText(Text text) {
    for (int i = 0; i < text.size; ++i) {
        wprintf(L"%ls\n",text.sentences[i].words);
    }
    freeText(text);
}