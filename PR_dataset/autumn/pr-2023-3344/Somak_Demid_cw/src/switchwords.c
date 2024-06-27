
#include "switchwords.h"

void switchwords(Text* structure,wchar * word){
    int priotlen = wcslen(word)-1;
    for (int i = 0; i < structure->countsents;i++){
        for (int j = 0; j < structure->arrofsents[i]->countwords;j++){
            if (wcslen(structure->arrofsents[i]->arrofwords[j]) > priotlen){
                structure->arrofsents[i]->arrofwords[j] = L"(большое слово)";
            }
        }
    }
}
