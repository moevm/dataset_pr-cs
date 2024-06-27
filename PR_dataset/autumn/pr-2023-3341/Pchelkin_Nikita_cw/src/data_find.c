#include "data_find.h"

int wtoi(wchar_t* str){
    int result = 0;
    int digit_place = 1;
    for(int i = wcslen(str)-1; i >= 0; i--){
        if(!iswdigit(str[i])) return -1;
        result += digit_place*(str[i]- L'0');
        digit_place *= 10;
    }
    return result;
}

void data_find(struct Text* text){
    wchar_t* months[] = {L"января", L"февраля", L"марта", L"апреля", L"мая", L"июня", L"июля", L"августа", L"сентября", L"октября", L"ноября", L"декабря"};
    int day, month, year;
    int flag;
    wchar_t data[11];
    wchar_t* old_data;
        for(int i = 0; i < text->size-1; i++) {
            if(text->text[i].num_of_words < 4) continue;
            flag = 0;
            day = wtoi(text->text[i].words[text->text[i].num_of_words-4]);
            year = wtoi(text->text[i].words[text->text[i].num_of_words-2]);
            if(day >= 32 || day <= 0 || year <= 0 || year >= 10000) continue;
            for(int j = 0; j < 12; j++){
                if(wcsstr(text->text[i].words[text->text[i].num_of_words-3], months[j])){
                    old_data = (wchar_t*)calloc(22, sizeof(wchar_t));
                    for(int k = 4; k > 1; k--){
                        wcscat(old_data, text->text[i].words[text->text[i].num_of_words-k]);
                        wcscat(old_data, L" ");
                    }
                    wcscat(old_data, L"г.");

                    if(wcsstr(text->text[i].sentence, old_data)){
                        flag++;
                        month = j+1;
                        swprintf(data, 11, L"%02d/%02d/%04d", day, month, year);
                    }
                }
            }
            if(flag){
                for(int j = 0; j < wcslen(data); j++){
                    text->text[i].sentence[wcslen(text->text[i].sentence)- wcslen(old_data)+j] = data[j];
                }
                text->text[i].sentence[wcslen(text->text[i].sentence)- wcslen(old_data)+ wcslen(data)] = L'.';
                text->text[i].sentence[wcslen(text->text[i].sentence)- wcslen(old_data)+ wcslen(data)+1] = L'\0';
                text->text[i].size = wcslen(text->text[i].sentence);
                
            }
        }
}