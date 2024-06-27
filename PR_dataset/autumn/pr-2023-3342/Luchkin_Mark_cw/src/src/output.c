#include "output.h"

void printCwInfo() {
    wprintf(L"Course work for option 5.2, created by Mark Luchkin.\n");
}

void printText(Text text){
    for (int i = 0; i < text.size; i++){
        wprintf(L"%ls\n", text.sentences[i].chars);
    }

    wprintf(L"\n");
}

void printNeededSentences(Text text){
    for (int i = 0; i < text.size; i++){
        if (text.sentences[i].wordCounter > 5  || text.sentences[i].wordCounter < 2){
            continue;
        }
        wprintf(L"%ls\n", text.sentences[i].chars);
    }
}

void isSameLetters(Text text, wchar_t* frstWord){
    for (int i = 0; i < text.size; i++){
        wchar_t* tokenBuffer;
        wchar_t* word = wcstok(wcsdup(text.sentences[i].chars), L" ,.", &tokenBuffer);
        while(word != NULL){
            int c = 0;
            for (int j = 0; j < wcslen(word); j++){
                wchar_t* ch = malloc(2 * sizeof(wchar_t));
                ch[0] = towlower(word[j]);
                if (wcsstr( frstWord,  ch) != NULL){
                    c++;
                    continue;
                } else{
                    break;
                }
            }
            if (c == wcslen(word)){
                wprintf(L"%ls\n", word);
            }

            word = wcstok(NULL, L" ,.", &tokenBuffer);
        }
    }
}
