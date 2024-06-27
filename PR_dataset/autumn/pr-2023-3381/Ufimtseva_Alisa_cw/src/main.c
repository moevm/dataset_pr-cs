#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

#include "structs.h"
#include "functions.h"
#include "input_function.h"
#include "text_processing_function.h"
#include "free_memory_func.h"

int main(){
    setlocale(LC_ALL, "");
    wprintf(L"Course work for option 5.16, created by Alisa Ufimtseva.\n");
    int znach;
    int n;
    wscanf(L"%d",&znach);
    //wprintf(L"%d",znach);
    if (znach==5){
        //wprintf(L"!!!");
        func5();
        return 0;
    }
    if (znach==9){
        wchar_t c=getwchar();
        c=getwchar();
        wchar_t* sent=(wchar_t*)malloc(sizeof(wchar_t)*1);
        int pos=0;
        while (c!=L'\n'){
            sent[pos]=c;
            pos++;
            sent=(wchar_t*)realloc(sent,  (pos+1)* sizeof(wchar_t));
            c=getwchar();
        }
        sent[pos]=L'!';
        struct Text text = input_text(text);
        nine(sent,text,pos+1);
        return 0;
    }
    if (znach==8){
        struct Text text = input_text(text);
        eight(text);
        return 0;
    }
    if (znach<0 || znach>5){
        wprintf(L"Error: Такого действия не существует.\n");
        return 0;
    }
    //wprintf(L"URAURAURA");
    struct Text text = input_text(text);
    //wprintf(L"URAURAURA");
    switch(znach){
        case 0:
            //wprintf(L"omagod");
            text_processing(text);
            free_memory(text, text.amount_of_sentences);                                                                                //ok
            return 0;
        case 1:
            last_is_num(text);
            free_memory(text, text.amount_of_sentences);                                                                               //ok
            return 0;
        case 2:
            last_in_sentence(text);
            free_memory(text, text.amount_of_sentences);                                                                                        //ok
            return 0;
        case 3:
            qsort(text.sentences, text.amount_of_sentences, sizeof(struct Sentence*),cmp);
            text_processing(text);
            free_memory(text, text.amount_of_sentences);                                                                                        //ok
            return 0;
        case 4:
            n=text.amount_of_sentences;
            text=delete_small_sentences(text);
            //wprintf(L"%d\n",text.amount_of_sentences);
            /*for (int i=0;i<text.amount_of_sentences;i++){
                wprintf(L"%ls\n",text.sentences[i]->sentence);
            }*/
            text_processing(text);
            free_memory(text, n);                                                                                        //ok
            return 0;          
    }
}
