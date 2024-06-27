#include "find_middle_time_and_translate.h"

// Заменить в тексте все подстроки “high noon” на “полдень” и “полночь” на “midnight”.
void find_middle_time_and_translate(text_t* text)
{
    for(size_t i = 0; i < text->size; ++i){
        text->data[i]->data = (wchar_t*)realloc(text->data[i]->data, sizeof(wchar_t) * (wcslen(text->data[i]->data) + wcslen(text->data[i]->data) / 5));
        wchar_t* curline = text->data[i]->data;
        // 0123полночь456789. -> 0123midnight456789
        wchar_t find[7] = L"полночь";
        wchar_t replace[8] = L"midnight";
        int match_ind = 0;
        for(size_t j = 0; j < text->data[i]->size; ++j){
            if(find[match_ind] == curline[j]){
                match_ind++;
            } else {
                match_ind = 0;
                if(curline[j] == L'п')
                    match_ind = 1;
            }
            if(match_ind == 7){
                text->data[i]->size++;
                curline[text->data[i]->size] = L'\0';
                // 0123полночь456789. -> 0123полночь4456789.
                for(int k = (wcslen(curline)); k > j + 1; --k){
                    curline[k] = curline[k - 1];
                }
                for(int k = j + 1 - match_ind; k < j + 2; ++k){
                    curline[k] = replace[k - j - 1 + match_ind];
                }
                match_ind = 0;
            }
        }
        
        wchar_t find2[9] = L"high noon";
        wchar_t replace2[7] = L"полдень";
        match_ind = 0;
        for(size_t j = 0; j < text->data[i]->size; ++j){
            if(find2[match_ind] == curline[j]){
                match_ind++;
            } else {
                match_ind = 0;
                if(curline[j] == L'h')
                    match_ind = 1;
            }
            if(match_ind == 9){
                text->data[i]->size = text->data[i]->size - 2;
                for(int k = j - match_ind + 1; k < j - 1; ++k){
                    curline[k] = replace2[k - j + match_ind - 1];
                }
                for(int k = j - 1; k < wcslen(curline); ++k){
                    curline[k] = curline[k + 2];
                }
                curline[text->data[i]->size] = L'\0';
                match_ind = 0;
                j -= 2;
            }
        }
        
        curline = NULL;
    }
}