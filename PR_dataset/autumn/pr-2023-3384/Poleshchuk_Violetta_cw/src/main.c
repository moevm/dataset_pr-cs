#include <stdio.h>
#include <wctype.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include "header_files/inputText.h"
#include "header_files/structures.h"
#include "header_files/getChoise.h"
#include "header_files/makeDate.h" 
#include "header_files/reverseWithPunctuation.h"
#include "header_files/sort.h"
#include "header_files/delete.h"
#include "header_files/helpAboutFunctions.h"


wchar_t* makeLower(wchar_t* word);
int main(){
    setlocale(LC_ALL, "");
    wprintf(L"Course work for option 5.8, created by Violetta Poleschschuk.\n");
    int choise = getChoise();
    Text text; 
    if (choise == 9){
        int lenWord = 0;
            int volumeW = 1;
            wchar_t symbol;
            wchar_t* newWord = malloc(sizeof(wchar_t)*volumeW);
            do{
                symbol = getwchar();
                if (symbol != '\n'){
                    newWord[lenWord++] = symbol;
                }
                if (lenWord >= volumeW){
                    volumeW *= 2;
                    newWord = realloc(newWord, sizeof(wchar_t)*volumeW);
                }

            }while(symbol != '\n');
            /* int lenn = 0;
            int volume = 1;
            wchar_t* newWord = malloc(volume * sizeof(wchar_t));
            wchar_t symbol;
            do{
                symbol = getwchar();
                if (symbol != '\n'){
                    newWord[lenn++] = symbol;
                }
                if (lenn >= volume){
                    volume *= 2;
                    newWord = realloc(newWord, volume*sizeof(wchar_t));
                }
            }while(symbol != '\n'); */
            wchar_t* word = makeLower(newWord);

            text = madeText();

            for (int i = 0; i < text.countSentences; i++){
                for (int j = 0; j < text.sentences[i].counterWords; j++){
                    int count = 0;
                    for (int k = 0; k < wcslen(text.sentences[i].words[j].symbols); k++){
                        if ((wcschr(word, towlower(text.sentences[i].words[j].symbols[k])))!=NULL){
                            count++;
                        }
                    }
                    if (count == wcslen(text.sentences[i].words[j].symbols)){
                        wprintf(L"%ls\n", text.sentences[i].words[j].symbols);
                    }
                }
                
            }
            return 0;

    }
    switch(choise){
        case 0:
            text = madeText();
            output(text);
            break;
        case 1:
            text = madeText();
            makeDate(text);
            break;
        case 2:
            text = madeText();
            reverseWithPunctuation(text);
            break;
        case 3:
            text = madeText();
            sort(text);
            break;
        case 4:
            text = madeText();
            delete(text);
            break;
        case 5:
            outputPrint();
            break;

        default:
            wprintf(L"Неверно введена функция");
    }
}

wchar_t* makeLower(wchar_t* word){
    wchar_t* copy = malloc(wcslen(word)*sizeof(wchar_t));
    for (int i = 0; i < wcslen(word); i++){
        copy[i] = towlower(word[i]);
    }
    return copy;
}