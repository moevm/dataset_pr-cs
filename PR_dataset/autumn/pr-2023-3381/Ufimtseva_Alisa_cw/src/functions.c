#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include "structs.h"
#include "free_memory_func.h"

void last_is_num(struct Text text){
    wchar_t* nums[10] ={L"ноль",L"один",L"два",L"три",L"четыре",L"пять",L"шесть",L"семь",L"восемь",L"девять"};
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
            for (int k=0;k<=text.sentences[i]->amount_of_letters;k++){
                if (text.sentences[i]->sentence[k]>=L'0' && text.sentences[i]->sentence[k]<=L'9' && !(iswalnum(text.sentences[i]->sentence[k+1]))){
                     for (int t=0;t<wcslen(nums[text.sentences[i]->sentence[k]-'0']);t++){
                        wprintf (L"%lc", nums[text.sentences[i]->sentence[k]-'0'][t]);
                     }
                }
                else{
                    wprintf (L"%lc", text.sentences[i]->sentence[k]);
                }
            }
            wprintf(L"\n");
        }
    }
}

void last_in_sentence(struct Text text){
    int exist[text.amount_of_sentences];
    for (int i=0;i<text.amount_of_sentences;i++){
        exist[i]=0;
        text.sentences[(text.amount_of_sentences-1+i)%text.amount_of_sentences]->last_word;
        for (int j=0;j<text.sentences[i]->amount_of_letters-text.sentences[(text.amount_of_sentences-1+i)%text.amount_of_sentences]->len_last_word;j++){
            //wprintf(L"%d ",j);
            if ((j==0 || !(iswalnum(text.sentences[i]->sentence[j-1]))) && text.sentences[i]->sentence[j]==text.sentences[(text.amount_of_sentences-1+i)%text.amount_of_sentences]->last_word[0]){
                //wprintf(L"!%d! ",j);
                int l=1;
               // wprintf(L"?%d? ",text.sentences[(text.amount_of_sentences-1+i)%text.amount_of_sentences]->len_last_word);
                while (text.sentences[i]->sentence[j+l]==text.sentences[(text.amount_of_sentences-1+i)%text.amount_of_sentences]->last_word[l] && l<text.sentences[(text.amount_of_sentences-1+i)%text.amount_of_sentences]->len_last_word){
                    l++;
                }
              //  wprintf(L"(%d) ",l);
                if (l==text.sentences[(text.amount_of_sentences-1+i)%text.amount_of_sentences]->len_last_word && !(iswalnum(text.sentences[i]->sentence[j+l]))){
                    //wprintf(L"*%lc* ",text.sentences[i]->sentence[j+l]);
                    exist[i]=1;
                    int q=0;
                    for (int k=0;k<i;k++){
                        int w=0;//есть ли разные буквы
                        if (exist[k]){
                            if (text.sentences[i]->amount_of_letters==text.sentences[k]->amount_of_letters){
                                for (int l=0;l<text.sentences[i]->amount_of_letters;l++){
                                    if (text.sentences[i]->sentence_low[l]!=text.sentences[k]->sentence_low[l]){
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
                        else{
                            q++;
                        }
                    }
                    //wprintf(L"????\n");
                    //wprintf(L"%d %d\n",i,q);
                    if (q==i){
                        for (int t=0;t<j;t++){
                            wprintf (L"%lc", text.sentences[i]->sentence[t]);
                        }
                        for (int t=j; t<j+text.sentences[(text.amount_of_sentences-1+i)%text.amount_of_sentences]->len_last_word; t++){
                            wprintf(L"%s%lc%s", "\033[4;31m", text.sentences[i]->sentence[t], "\033[0m");
                        }
                        for (int t=j+text.sentences[(text.amount_of_sentences-1+i)%text.amount_of_sentences]->len_last_word;t<text.sentences[i]->amount_of_letters;t++){
                            wprintf (L"%lc", text.sentences[i]->sentence[t]);
                        }
                        wprintf (L"\n");
                        break;
                    }
                }
                else{
                    continue;
                }
            }
            else{
                continue;
            }
        }
    }
}

int cmp (const void *a, const void *b){
    const int f = (*(struct Sentence **)a)->amount_of_words;
    const int s = (*(struct Sentence **)b)->amount_of_words;
    if (f > s) {
        return -1;
    }
    if (f < s) {
        return 1;
    }
    else{
        return 0;
    }
}

struct Text delete_small_sentences(struct Text text){
   for (int i=0;i<text.amount_of_sentences;i++){
        //wprintf (L"%ls\n", text.sentences[i].sentence);
        if (text.sentences[i]->amount_of_words<=2){
           for (int j=i;j<text.amount_of_sentences-1;j++){
                struct Sentence* tmp=text.sentences[j];
                text.sentences[j]=text.sentences[j+1];
                text.sentences[j+1]=tmp;
            }
            /*free(text.sentences[text.amount_of_sentences-1]->sentence);
            free(text.sentences[text.amount_of_sentences-1]->sentence_low);
            free(text.sentences[text.amount_of_sentences-1]->last_word);
            free(text.sentences[text.amount_of_sentences-1]);*/
            text.amount_of_sentences--;
            i--;
        }
    }
    //wprintf(L"%d\n",text.amount_of_sentences);
    return text;
}

void func5(){
    wprintf(L"Программа должна выполнить одно из введенных пользователем действий и завершить работу:\n");
    wprintf(L"\tДействие 1 - программе необходимо изменить все слова в тексте заканчивающиеся на символ цифры (0-9) так чтобы они заканчивались на название цифры на кириллице.\n");
    wprintf(L"\tДействие 2 - программе необходимо вывести все предложения в которых встречается последнее слово предыдущего предложения. Данное слово необходимо выделить, подчеркнув красным цветом.\n");
    wprintf(L"\tДействие 3 - программе необходимо отсортировать предложения по уменьшению количества слов в предложении.\n");
    wprintf(L"\tДействие 4 - программе необходимо удалить все предложения в которым два и меньше слова.\n");
    wprintf(L"\tДействие 5 - программе необходимо вывести справки о функциях, которые реализует программа.\n");
}

void nine(wchar_t* sent, struct Text text, int lensent){
    //wprintf(L"!!!!!");
    for (int i=0;i<text.amount_of_sentences;i++){
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
        if (q==i){
            //wprintf(L"!!!!!");
            int vyvod=1;
            int start=0;
            int pos=0;
            int ex=0;
            while (text.sentences[i]->sentence[pos]!=L'.'){
                while (text.sentences[i]->sentence[pos]!=L' ' && text.sentences[i]->sentence[pos]!=L',' && text.sentences[i]->sentence[pos]!=L'.'){
                    pos++;
                }
                int len=pos-start;
                int k=0;
                while (lensent>len && sent[k+len-1]!=L'!'){
                    if (towlower(text.sentences[i]->sentence[start])==towlower(sent[k])){
                        if (k==0 || sent[k-1]==L' '){
                            int good=1;
                            for (int h=1;h<len;h++){
                                if (towlower(text.sentences[i]->sentence[start+h])==towlower(sent[k+h])){
                                    good++;
                                }
                            }
                            if (good==len && (sent[k+len]==L' ' || sent[k+len]==L'!')){
                                ex=1;
                            }
                        }
                    }
                    k++;
                }
                if (ex==0){
                    vyvod=0;
                }
                while (text.sentences[i]->sentence[pos]==L' ' || text.sentences[i]->sentence[pos]==L','){
                    pos++;
                }
                start=pos;
                //vyvod=1;
                ex=0;
            }
            if (vyvod==1){
                for (int l=0;l<text.sentences[i]->amount_of_letters;l++){
                    wprintf (L"%lc", text.sentences[i]->sentence[l]);
                }
                wprintf(L"\n");
            }
        }
    }
}

void eight(struct Text text){
    for (int i=0;i<text.amount_of_sentences;i++){
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
        if (q==i){
            int x=1;
            int l=0;
            int r=text.sentences[i]->amount_of_letters-2;
            //wprintf (L"%lc\n", text.sentences[i]->sentence[r]);
            while (r>l){
                while (text.sentences[i]->sentence[l]==L' ' || text.sentences[i]->sentence[l]==L','){
                    l++;
                }
                while (text.sentences[i]->sentence[r]==L' ' || text.sentences[i]->sentence[r]==L','){
                    r--;
                }
                if (towlower(text.sentences[i]->sentence[l])!=towlower(text.sentences[i]->sentence[r])){
                    x=0;
                }
                r--;
                l++;
            }
            if (x==1){
                for (int l=0;l<text.sentences[i]->amount_of_letters;l++){
                    wprintf (L"%lc", text.sentences[i]->sentence[l]);
                }
                wprintf(L"\n");
            }
        }
    }
}