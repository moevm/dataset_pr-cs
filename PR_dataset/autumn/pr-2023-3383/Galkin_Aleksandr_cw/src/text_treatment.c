#include "text_treatment.h"
void release_text(struct Text txt)
{
    size_t length = (size_t)txt.length;
    for (size_t i = 0; i < length; i++)
    {
        free(txt.text[i]->sentence);
        free(txt.text[i]);
    }
    free(txt.text);
}
void translate_func(struct Sentence *str)
{
    wchar_t *first_check = {L"high noon"};
    wchar_t *first_change = {L"полдень"};
    wchar_t *second_check = {L"полночь"};
    wchar_t *second_change = {L"midnight"};
    while (wcsstr(str->sentence, first_check) != NULL)
    {
        size_t index = (size_t)(wcsstr(str->sentence, first_check) - str->sentence);
        wcsncpy(str->sentence + index, first_change, wcslen(first_change));
        wcsncpy(str->sentence + index + wcslen(first_change), str->sentence + index + wcslen(first_check), str->str_length - index - wcslen(first_check));
        str->sentence[str->str_length - wcslen(first_check) + wcslen(first_change)] = '\0';
        str->str_length = str->str_length - wcslen(first_check) + wcslen(first_change);
    }
    while (wcsstr(str->sentence, second_check) != NULL)
    {
        size_t index = (size_t)(wcsstr(str->sentence, second_check) - str->sentence);
        wchar_t *tmp = wcsdup(str->sentence+index+wcslen(second_check));
        wcsncpy(str->sentence + index, second_change, wcslen(second_change));
        if ((str->str_length + 3) / STEP > (str->str_length) / STEP)
            str->sentence = (wchar_t *)realloc(str->sentence, sizeof(wchar_t) * (wcslen(str->sentence) + STEP));
        str->str_length = str->str_length - wcslen(second_check) + wcslen(second_change);
        wcsncpy(str->sentence + index + wcslen(second_change), tmp, str->str_length - index - wcslen(second_check));
        free(tmp);
    }
}

void delete_sentences(struct Text txt)
{
    for (int i = 0; i < txt.length; i++)
    {
        wchar_t *sent_cpy = wcsdup(txt.text[i]->sentence);
        wchar_t *first_word, *last_word, *token, *ptr;
        token = wcstok(sent_cpy, L" ,.", &ptr);
        first_word = wcsdup(token);
        while (token != NULL)
        {
            last_word = token;
            token = wcstok(NULL, L" ,.", &ptr);
        }
        if (wcscmp(first_word, last_word) != 0)
        {
            wprintf(L"%ls\n", txt.text[i]->sentence);
        }
        free(first_word);
        free(sent_cpy);
    }
}
void func9(struct Text txt){
    for(int i = 0; i<txt.length; i++){
        int f = 1;
        for(int k = 1; k < wcslen(txt.text[i]->sentence); k++){
            wchar_t low1 = towlower(txt.text[i]->sentence[k-1]);
            wchar_t low2 = towlower(txt.text[i]->sentence[k]);
            if(low1!=low2 && f!=1){
                wprintf(L"%lc%d", towupper(txt.text[i]->sentence[k-1]),f);
                f = 1;
            }
            else if(low1 == low2){
                f+=1;
            }
            else{
                wprintf(L"%lc", txt.text[i]->sentence[k-1]);
            }
        }
        wprintf(L".\n");
    }
}