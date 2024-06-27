#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include "structures.h"
#include "replace_digits.h"
wchar_t* concat_part(wchar_t* str,size_t first_ind, size_t last_index) {
    wchar_t* result = malloc(sizeof(wchar_t)*(last_index-first_ind+2));
    if (result==NULL){
        wprintf(L"Error: failed to allocate memory for result [function: concat_part]\n");
        exit(1);
    }
    size_t ind_result = 0;
    for (size_t i = first_ind;i<last_index+1;i++){
        result[ind_result++] = str[i];
    }
    result[last_index-first_ind+1] = '\0';
    return result;
}
size_t digits_in_number(size_t num){
    size_t digits = 0;
    size_t temp = num;
    while (temp!=0){
        digits++;
        temp/=10;
    }
    return digits;
}
void replace_digits(struct Text* text){
    wchar_t nums[] = {L'0',L'1',L'2',L'3',L'4',L'5',L'6',L'7',L'8',L'9'};
    size_t counts[] = {0,0,0,0,0,0,0,0,0,0};
    for (size_t i = 0;i<text->len;i++){
        for (size_t j = 0;j<text->text[i]->len;j++){
            for (size_t k = 0;k<10;k++){
                if (nums[k]==text->text[i]->sentence[j]){
                    counts[k]++;
                }
            }
        }
    }
    for (size_t i = 0;i<text->len;i++){
        for (size_t j = 0;j<10;j++){
            size_t index[text->text[i]->len];
            size_t len_index = 0;
            for (size_t k = 0;k<text->text[i]->len;k++){
                if (nums[j]==text->text[i]->sentence[k]){
                    index[len_index++]=k;
                }
            }
            if (counts[j]!=0){
                size_t max_len = digits_in_number(counts[j]);
                wchar_t* ch = malloc(sizeof(wchar_t)*(max_len+1));
                if (ch==NULL){
                    wprintf(L"Error: failed to allocate memory for ch [function: replace_digits]\n");
                    exit(1);
                }
                ch[max_len] = '\0';
                swprintf(ch, max_len+1, L"%ld",counts[j]);
                size_t diff = wcslen(ch)-1;
                for (size_t k = 0;k<len_index;k++){
                    size_t ind = index[k]+text->text[i]->diff_index;
                    wchar_t* new_str = malloc((text->text[i]->len+diff+1)*sizeof(wchar_t));
                    if (new_str==NULL){
                        wprintf(L"Error: failed to allocate memory for new_str [function: replace_digits]\n");
                        exit(1);
                    }
                    new_str[text->text[i]->len+diff]='\0';
                    wchar_t* concat = concat_part(text->text[i]->sentence, 0, ind-1);
                    wcscpy(new_str, concat);
                    free(concat);
                    wcscat(new_str, ch);
                    wchar_t* concat2 = concat_part(text->text[i]->sentence, ind+1, wcslen(text->text[i]->sentence)-1);
                    wcscat(new_str,concat2);
                    free(concat2);
                    text->text[i]->diff_index+=diff;
                    text->text[i]->sentence = realloc(text->text[i]->sentence,(wcslen(new_str)+1)*sizeof(wchar_t));
                    wcsncpy(text->text[i]->sentence,new_str,wcslen(new_str)+1);
                    if (text->text[i]->sentence==NULL){
                        wprintf(L"Error: failed to allocate memory for sentence [function: replace_digits]\n");
                        exit(1);
                    }
                    text->text[i]->len+=diff;
                    free(new_str);
                }
                text->text[i]->diff_index = 0;
                free(ch);
            }
        }
    }

    for (int i = 0;i<text->len;i++){
        wprintf(L"%ls.\n",text->text[i]->sentence);
    }

}