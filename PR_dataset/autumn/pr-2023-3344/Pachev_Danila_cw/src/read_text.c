#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include "read_text.h"
#include "structures.h"
void read_text(struct Text *text){

    text->text = (struct Sentence**)malloc(sizeof(struct Sentence*));
    if (text->text==NULL){
        wprintf(L"Error: failed to allocate memory for text [function: read_text]\n");
        exit(1);
    }
    text->count_all_words=0;
    int newline_count = 0;
    text->len=0;
    while (newline_count<2){
        struct Sentence *sentence = (struct Sentence*)malloc(sizeof(struct Sentence));
        if (sentence==NULL){
            wprintf(L"Error: failed to allocate memory for struct Sentence [function: read_text]\n");
            exit(1);
        }
        sentence->sentence = (wchar_t*)malloc(sizeof(wchar_t));
        if (sentence->sentence==NULL){
            wprintf(L"Error: failed to allocate memory for sentence->sentence [function: read_text]\n");
            exit(1);
        }
        sentence->len=0;
        wchar_t ch='0';
        while ((ch!=L'.')){
            ch = getwchar();
            if (ch==L'\n'){
                newline_count++;
                if (newline_count==2){
                    break;
                }
            }
            else
                newline_count=0;

            sentence->sentence[sentence->len++]=ch;
            sentence->sentence = (wchar_t*)realloc(sentence->sentence,sizeof(wchar_t)*((sentence->len)+1));
            if (sentence->sentence==NULL){
                wprintf(L"Error: failed to reallocate memory for sentence->sentence [function: read_text]\n");
                exit(1);
            }
        }
        // добавляем предложение только тогда, когда предложение не содержит 2-х \n, либо если пользователь забыл поставить . в последнем предложении
        if (newline_count<2 || (newline_count>=2 && sentence->len>2)){
            sentence->sentence[sentence->len]='\0';
            // удаляем лишние пробелы в начале предложения
            while (sentence->sentence[0]==L' ' || sentence->sentence[0]==L'\t' || sentence->sentence[0]==L'\n'){
                wmemmove(sentence->sentence, (sentence->sentence)+1, sentence->len);
                sentence->len--;
            }
            sentence->diff_index = 0;
            if (sentence->sentence[sentence->len-1]==L'.'){
                sentence->sentence = realloc(sentence->sentence, sizeof(wchar_t)*(sentence->len));
                if (sentence->sentence==NULL){
                    wprintf(L"Error: failed to reallocate memory for sentence->sentence [function: read_text]\n");
                    exit(1);
                }
            }

            sentence->sentence[sentence->len-1] = '\0';
            sentence->len--;
            int flag = 0;
            // проверяем на наличие дубликата преложения
            for (size_t i = 0;i<text->len;i++){
                if (wcscasecmp(text->text[i]->sentence, sentence->sentence)==0){
                    flag = 1;
                }
            }
            // добавляем в текст, если не было дубликата
            if (flag!=1){
                wchar_t* ptr;
                wchar_t* copy = wcsdup(sentence->sentence);
                if (copy==NULL){
                    wprintf(L"Error: failed to allocate memory for copy [function: read_text]\n");
                    exit(1);
                }
                size_t words_count = 0;
                wchar_t* token = wcstok(copy, L", .\n", &ptr);
                wchar_t** split_sent = malloc(sizeof(wchar_t*));
                if (split_sent==NULL){
                    wprintf(L"Error: failed to allocate memory for split_sent [function: read_text]\n");
                    exit(1);
                }
                while (token) {
                    split_sent = realloc(split_sent,(sizeof(wchar_t*)*(1+words_count)));
                    if (split_sent==NULL){
                        wprintf(L"Error: failed to reallocate memory for split_sent [function: read_text]\n");
                        exit(1);
                    }
                    split_sent[words_count++] = wcsdup(token);
                    if (split_sent[words_count-1]==NULL){
                        wprintf(L"Error: failed to allocate memory for split_sent[words_count-1] [function: read_text]\n");
                        exit(1);
                    }
                    token = wcstok(NULL, L", .\n", &ptr);
                }
                text->count_all_words+=words_count;
                text->text[text->len++]=sentence;
                text->text = (struct Sentence**)realloc(text->text, sizeof(struct Sentence*)*(text->len+1));
                if (text->text==NULL){
                    wprintf(L"Error: failed to reallocate memory for text->text [function: read_text]\n");
                    exit(1);
                }
                for (size_t i = 0;i<words_count;i++){
                    free(split_sent[i]);
                }
                free(split_sent);
                free(copy);
            }
        }
    }
}