#include <stdlib.h>
#include <string.h>
#include <wctype.h>
#include "text_processing_function.h"
#include "structs.h"

void text_processing(struct Text text){
    //wprintf(L"!!!!\n");
    //wprintf(L"%d\n",text.amount_of_sentences);
    for (int i=0;i<text.amount_of_sentences;i++){
        //wprintf(L"%d ", i);
        //puts(text.sentences[i].sentence);
        int q=0;//есть ли одинаковые предложения
        for (int j=0;j<i;j++){
            int w=0;//есть ли разные буквы
            if (text.sentences[i]->amount_of_letters==text.sentences[j]->amount_of_letters){
                for (int l=0;l<text.sentences[i]->amount_of_letters;l++){
                    if (text.sentences[i]->sentence_low[l]!=text.sentences[j]->sentence_low[l]){
                        w=1;
                        //wprintf(L"aaaaa");
                        break;
                    }
                }
            }
            else{
                w=1;
                //wprintf(L"bbbbb");
            }
            if (w==1){
                q++;//есть одинаковые предложения
            }
        }
        //wprintf(L"????\n");
        //wprintf(L"%d %d\n",i,q);
        if (q==i){
            wprintf (L"%ls\n", text.sentences[i]->sentence);
        }
    }
}