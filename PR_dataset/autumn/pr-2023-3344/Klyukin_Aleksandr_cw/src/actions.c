#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

#include "structures.h"
#include "sortComp.h"

void palindroms(struct Text *text, int lenghts, int dot){
    for(int i = 0; i<text->len;i++){
        struct Text *newText = malloc(sizeof(struct Text));
        newText->len = text->len;
        
        // Выделение памяти под массив указателей на структуры Sentence
        newText->sentences = malloc(text->len * sizeof(struct Sentence*));
        
        // Копирование содержимого массива из исходной структуры Text
        for (int d = 0; d < text->len; d++) {
            // Выделение памяти под новую строку и копирование содержимого из исходной структуры Sentence
            newText->sentences[d] = malloc(sizeof(struct Sentence));
            newText->sentences[d]->len = text->sentences[d]->len;
            newText->sentences[d]->sentence = malloc((text->sentences[d]->len + 1) * sizeof(wchar_t));
            wcscpy(newText->sentences[d]->sentence, text->sentences[d]->sentence);
        }

        wchar_t* line = (wchar_t*)malloc(100 * sizeof(wchar_t));
        line[0] = L'\0';
        wchar_t *input = newText->sentences[i]->sentence;
        wchar_t *word = wcstok(input, L" :!,.-\n", &input);
        while (word != NULL) {
        line = (wchar_t*)realloc(line, (wcslen(line) + wcslen(word) + 1) * sizeof(wchar_t));
        wcscat(line, word);
        word = wcstok(NULL, L" :!,.-\n", &input);
        }
        int cnt = 0;
        for(int symb=0; symb<wcslen(line)/2;symb++){
            //wprintf(L"_%lc_ _%lc_\n", towupper(line[symb]), towupper(line[wcslen(line)-symb-1]));
            if(towupper(line[symb]) == towupper(line[wcslen(line)-symb-1])){
                cnt = cnt + 1;
            }
            if(towlower(line[symb]) != towlower(line[wcslen(line)-symb-1])){
                break;
            }
        }
        if(cnt == wcslen(line)/2){
            wprintf(L"%ls", text->sentences[i]->sentence);
            if(i == text->len-1){
                if(dot == 1){
                    wprintf(L".");
                }
            }
            if(i != text->len-1){
                wprintf(L".");
            }
            wprintf(L"\n");
        }
        
    }
}

void coloredOut(struct Text *text, int lenghts, int dot){
    for(int i; i<text->len; i++){
        int wordLen = 0;
        struct Text *newText = malloc(sizeof(struct Text));
        newText->len = text->len;
        
        // Выделение памяти под массив указателей на структуры Sentence
        newText->sentences = malloc(text->len * sizeof(struct Sentence*));
        
        // Копирование содержимого массива из исходной структуры Text
        for (int d = 0; d < text->len; d++) {
            // Выделение памяти под новую строку и копирование содержимого из исходной структуры Sentence
            newText->sentences[d] = malloc(sizeof(struct Sentence));
            newText->sentences[d]->len = text->sentences[d]->len;
            newText->sentences[d]->sentence = malloc((text->sentences[d]->len + 1) * sizeof(wchar_t));
            wcscpy(newText->sentences[d]->sentence, text->sentences[d]->sentence);
        }
        wchar_t *input = text->sentences[i]->sentence;
        wchar_t *word = wcstok(input, L" ,.-\n", &input);
        while (word != NULL) {
            wordLen = wcslen(word)%4;
            switch (wordLen)
            {
            case 0: // red
                wprintf(L"\033[1;31m%ls", word);
                break;
            case 1: // blue
                wprintf(L"\033[1;34m%ls", word);
                break;
            case 2: // green
                wprintf(L"\033[1;32m%ls", word);
                break;
            case 3: // yellow
                wprintf(L"\033[1;33m%ls", word);
                break;
            default:
                break;
            }
            wprintf(L"\033[0m");
            lenghts = 0;
            if (input){
                if((iswpunct(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input)]) || iswspace(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input)]))){
                    lenghts = 0;
                    while (iswpunct(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]) || iswspace(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]))
                    {
                        lenghts+=1;
                    }
                    lenghts-=1;
                    
                    while (iswpunct(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]) || iswspace(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]))
                    {
                        wprintf(L"%c", newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]);
                        lenghts-=1;
                    }     
                }
                
                else if((!iswpunct(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]) && !iswspace(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]))){
                    while (!iswpunct(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]) && !iswspace(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]))
                    {
                        lenghts+=1;
                    }
                    while (iswpunct(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]) || iswspace(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]))
                    {
                        lenghts+=1;
                    }
                    lenghts-=1;
                    while (iswpunct(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]) || iswspace(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]))
                    {
                        if(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts] != 10){             
                            wprintf(L"%c", newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]);
                        }
                        if(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts] == 10){             
                            wprintf(L" ");
                        }
                        lenghts-=1;
                    }
                }
            }

            word = wcstok(NULL, L" ,.-\n", &input);
        }
        if(i+1 == text->len){
            if(dot){
                wprintf(L".");
            }
        }
        if(i+1 != text->len){
            wprintf(L".");
        }
        wprintf(L"\n");
        for (int h = 0; h < newText->len; h++) {
            free(newText->sentences[h]->sentence);
            free(newText->sentences[h]);
        }
        free(newText->sentences);
        free(newText);
        
    }
}

void HihghtSigns(struct Text *text){
    int cntr = 0;
    for(int i = 0; i<text->len;i++){
        wchar_t *input = text->sentences[i]->sentence;
        wchar_t *word = wcstok(input, L" ,.\n", &input);
        while (word != NULL) {
        if (iswalpha(word[0]) && iswalpha(word[wcslen(word) - 1])){
            if(iswupper(word[0]) && iswupper(word[wcslen(word) - 1])){
                wprintf(L"%ls в предложении № %d\n", word, i+1);
                cntr+=1;
            }
        }
        word = wcstok(NULL, L" ,.\n", &input);
        }
    }
    if(cntr == 0){
        wprintf(L"Error: Oops!, нету таких предложений.\n");
    }

}

void sortSentencesByLastWordLength(struct Text *text) {
    if (text->len != 1){
        qsort(text->sentences, text->len, sizeof(struct Sentence *), compare);
    }
    
    for (int i = 0; i < text->len; i++) {
        if(text->sentences[i]->sentence[wcslen(text->sentences[i]->sentence)-1] == 10){
            wprintf(L"%ls", text->sentences[i]->sentence);
        }
        else{
            wprintf(L"%ls.\n", text->sentences[i]->sentence);
        }
    }
}

void deleteDigits(struct Text *text, int lenghts, int dot){
    for(int i; i<text->len; i++){
        int cnts = 0;
        struct Text *newText = malloc(sizeof(struct Text));
        newText->len = text->len;
        
        // Выделение памяти под массив указателей на структуры Sentence
        newText->sentences = malloc(text->len * sizeof(struct Sentence*));
        
        // Копирование содержимого массива из исходной структуры Text
        for (int d = 0; d < text->len; d++) {
            // Выделение памяти под новую строку и копирование содержимого из исходной структуры Sentence
            newText->sentences[d] = malloc(sizeof(struct Sentence));
            newText->sentences[d]->len = text->sentences[d]->len;
            newText->sentences[d]->sentence = malloc((text->sentences[d]->len + 1) * sizeof(wchar_t));
            wcscpy(newText->sentences[d]->sentence, text->sentences[d]->sentence);
        }

        wchar_t *input = text->sentences[i]->sentence;
        wchar_t *word = wcstok(input, L" ,.-\n", &input);

        while (word != NULL) {

            for(lenghts = 0; lenghts<=wcslen(word); lenghts++){
                if(iswdigit(word[lenghts])){
                    cnts+=1;
                }
            }
            if (cnts != wcslen(word)){
                wprintf(L"%ls", word);
            }

            cnts = 0;
            lenghts = 0;
            if (input){
                
                if((iswpunct(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input)]) || iswspace(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input)]))){
                    lenghts = 0;
                    while (iswpunct(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]) || iswspace(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]))
                    {
                        lenghts+=1;
                    }
                    lenghts-=1;
                    
                    while (iswpunct(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]) || iswspace(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]))
                    {
                        wprintf(L"%c", newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]);
                        lenghts-=1;
                    }     
                }
                
                else if((!iswpunct(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]) && !iswspace(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]))){
                    while (!iswpunct(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]) && !iswspace(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]))
                    {
                        lenghts+=1;
                    }
                    while (iswpunct(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]) || iswspace(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]))
                    {
                        lenghts+=1;
                    }
                    lenghts-=1;
                    while (iswpunct(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]) || iswspace(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]))
                    {
                        if(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts] != 10){             
                            wprintf(L"%c", newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts]);
                        }
                        if(newText->sentences[i]->sentence[newText->sentences[i]->len - wcslen(input) - lenghts] == 10){             
                            wprintf(L" ");
                        }
                        lenghts-=1;
                    }
                }
            }

            word = wcstok(NULL, L" ,.-\n", &input);
        }
        if(i+1 == text->len){
            if(dot){
                wprintf(L".");
            }
        }
        if(i+1 != text->len){
            wprintf(L".");
        }
        wprintf(L"\n");
        for (int h = 0; h < newText->len; h++) {
            free(newText->sentences[h]->sentence);
            free(newText->sentences[h]);
        }
        free(newText->sentences);
        free(newText);
        
    }
}

void justOut(struct Text *text){
        for (int i = 0; i < text->len; i++) {
            if(i+1 == text->len){
                if(text->dotChecker){
                    wprintf(L"%ls.\n", text->sentences[i]->sentence);
                }
                else if(!text->dotChecker){
                    wprintf(L"%ls", text->sentences[i]->sentence);
                }
            }
            else{wprintf(L"%ls.\n", text->sentences[i]->sentence);}
            
        }
}
