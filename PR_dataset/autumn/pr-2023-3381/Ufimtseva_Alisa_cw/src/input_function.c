#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include "input_function.h"
#include "structs.h"

struct Text input_text(struct Text text){
    text.sentences=(struct Sentence**)malloc(sizeof(struct Sentence*)*1);
    text.sentences[0] =(struct Sentence *)malloc(sizeof(struct Sentence)*1);
    text.sentences[0]->sentence=(wchar_t*)malloc(sizeof(wchar_t)*1);
    text.sentences[0]->sentence_low=(wchar_t*)malloc(sizeof(wchar_t)*1);
    wchar_t letter=getwchar();
    //wprintf(L"%lc\n", letter);
    int amount_of_letters=0;
    int amount_of_sentences=0;
    int amount_of_words=1;
    int q=0;
    int last_space=-1;
    //wprintf(L"mamochki");
    while (1){
        if (letter==L'\n'){
            if (q==1){
                text.amount_of_sentences=amount_of_sentences;
                break;
            }
            else{
                q=1;
            }
        }
        else{
            q=0;
        }

        if (amount_of_letters!=0 && iswalnum(letter) && !(iswalnum(text.sentences[amount_of_sentences]->sentence[amount_of_letters-1]))){
            amount_of_words++;
        }

        if (amount_of_letters==0 && (letter==L' ' || letter==L'\n' || letter==L'\t' || letter==L'.' /*|| letter==L';' || letter==L'?' || letter==L'!'*/)){
            letter=getwchar();
            continue;
        }
        text.sentences[amount_of_sentences]->sentence=(wchar_t*)realloc(text.sentences[amount_of_sentences]->sentence,  (amount_of_letters+1)* sizeof(wchar_t));
        //wprintf(L"One\n");
        text.sentences[amount_of_sentences]->sentence_low=(wchar_t*)realloc(text.sentences[amount_of_sentences]->sentence_low,  (amount_of_letters+1)* sizeof(wchar_t));
        //wprintf(L"Two\n");
        text.sentences[amount_of_sentences]->sentence[amount_of_letters]=letter;
        if (text.sentences[amount_of_sentences]->sentence==NULL || text.sentences[amount_of_sentences]->sentence_low==NULL ){
            wprintf(L"1Error: Ошибка выделения памяти.\n");
            for (int i = 0; i < amount_of_sentences-1; i++) {
                free(text.sentences[i]->sentence);
                free(text.sentences[i]->sentence_low);
                free(text.sentences[i]->last_word);
                free(text.sentences[i]);
            }
            free(text.sentences[amount_of_sentences-1]->sentence);
            free(text.sentences[amount_of_sentences-1]->sentence_low);
            free(text.sentences[amount_of_sentences-1]);
            free(text.sentences);
            exit(0);
        }

        if (!(iswalnum(letter)) && !(letter==L'.' /*|| letter==L';' || letter==L'?' || letter==L'!'*/)){
            last_space=amount_of_letters;
        }

        if (iswupper(letter)){
            text.sentences[amount_of_sentences]->sentence_low[amount_of_letters]=towlower(letter); 
        }
        else{
            text.sentences[amount_of_sentences]->sentence_low[amount_of_letters]=letter;
        }
        amount_of_letters++;
        if (letter==L'.' /*|| letter==L';' || letter==L'?' || letter==L'!'*/){
            //wprintf(L"@@@\n");
            text.sentences[amount_of_sentences]->amount_of_words=amount_of_words;
            amount_of_words=1;
            //wprintf(L"%d",(i-last_space-1));
            //wprintf(L"%lc",text.sentences[amount_of_sentences].sentence[last_space+1]);
            text.sentences[amount_of_sentences]->len_last_word=amount_of_letters-last_space-2;
            text.sentences[amount_of_sentences]->last_word=(wchar_t*)malloc((amount_of_letters-last_space-1)*sizeof(wchar_t));
            if (text.sentences[amount_of_sentences]->last_word==NULL){
                wprintf(L"2Error: Ошибка выделения памяти.\n");
                for (int i = 0; i < amount_of_sentences; i++) {
                    free(text.sentences[i]->sentence);
                    free(text.sentences[i]->sentence_low);
                    free(text.sentences[i]->last_word);
                    free(text.sentences[i]);
                }
                free(text.sentences);
                exit(0);
            }
            for (int i=last_space+1;i<amount_of_letters-1;i++){
                text.sentences[amount_of_sentences]->last_word[i-last_space-1]=text.sentences[amount_of_sentences]->sentence[i];
                //wprintf(L"%d",(i-last_space-1));
            }
            text.sentences[amount_of_sentences]->last_word[amount_of_letters-last_space-2]=L'\0';
            //wprintf(L"%lc",text.sentences[amount_of_sentences].last_word);
            last_space=-1;
            text.sentences[amount_of_sentences]->sentence=(wchar_t*)realloc(text.sentences[amount_of_sentences]->sentence,  (amount_of_letters+1)* sizeof(wchar_t));
            text.sentences[amount_of_sentences]->sentence_low=(wchar_t*)realloc(text.sentences[amount_of_sentences]->sentence_low,  (amount_of_letters+1)* sizeof(wchar_t));
            if (text.sentences[amount_of_sentences]->sentence_low == NULL || text.sentences[amount_of_sentences]->sentence==NULL){
                wprintf(L"3Error: Ошибка выделения памяти.\n");
                for (int i = 0; i < amount_of_sentences; i++) {
                    free(text.sentences[i]->sentence);
                    free(text.sentences[i]->sentence_low);
                    free(text.sentences[i]->last_word);
                    free(text.sentences[i]);
                }
                free(text.sentences);
                exit(0);
            }   
            text.sentences[amount_of_sentences]->sentence[amount_of_letters]=L'\0';
            text.sentences[amount_of_sentences]->sentence_low[amount_of_letters]=L'\0';
            text.sentences[amount_of_sentences]->amount_of_letters=amount_of_letters;
            amount_of_letters=0;
            amount_of_sentences++;
            text.sentences=(struct Sentence**)realloc(text.sentences, sizeof(struct Sentence*)*(amount_of_sentences+1));
            if (text.sentences == NULL){
                wprintf(L"4Error: Ошибка выделения памяти.\n");
                for (int i = 0; i < amount_of_sentences; i++) {
                    free(text.sentences[i]->sentence);
                    free(text.sentences[i]->sentence_low);
                    free(text.sentences[i]->last_word);
                    free(text.sentences[i]);
                }
                free(text.sentences);
                exit(0);
            }    
            text.sentences[amount_of_sentences]=(struct Sentence *)malloc(sizeof(struct Sentence)*1);
            text.sentences[amount_of_sentences]->sentence=(wchar_t*)malloc(sizeof(wchar_t)*1);
            text.sentences[amount_of_sentences]->sentence_low=(wchar_t*)malloc(sizeof(wchar_t)*1);
            if (text.sentences[amount_of_sentences]->sentence==NULL || text.sentences[amount_of_sentences]->sentence_low==NULL){
                wprintf(L"5Error: Ошибка выделения памяти.\n");
                for (int i = 0; i < amount_of_sentences; i++) {
                    free(text.sentences[i]->sentence);
                    free(text.sentences[i]->sentence_low);
                    free(text.sentences[i]->last_word);
                    free(text.sentences[i]);
                }
                free(text.sentences);
                exit(0);
            }
        }
        letter=getwchar();
    }
    /*for (int i=0;i<text.amount_of_sentences;i++){
        //printf("%d ",text.amount_of_sentences);
        //wprintf (L"%ls\n", text.sentences[i].sentence);
        wprintf (L"%ls\n", text.sentences[i].last_word);
    }*/
    return text;
}
