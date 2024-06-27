#include "is_happened.h"

// Для всех вхождений дат в тексте вида “<day> <month> <year>,
// вывести эти даты в виде “DD.MM.YYYY” и строку “Happened” если эта дата была до текущей
// и “Not Happened” в противном случае. Например, для даты “03 Jan 1666” вывести “03.01.1666 Happened”.
void is_happened(text_t* words)
{
    time_t current_time = time(&current_time);
    u8 flag = 2;
	struct tm *time_info = (struct tm*)malloc(sizeof(struct tm));
    if(time_info == NULL) printError(L"Failed to allocate memory for the struct tm* [fn: is_happened]");
    if(words->size < 3) printError(L"too few words entered");

    wchar_t** word = (wchar_t**)malloc(sizeof(wchar_t*));
    if(word == NULL) printError(L"Failed to allocate memory for the wchar_t** [fn: is_happened]");
    for(u8 i = 0; i < 3; ++i){
        word[i] = (wchar_t*)malloc(sizeof(wchar_t) * 100);
        if(word[i] == NULL) printError(L"Failed to allocate memory for the wchar_t* [fn: is_happened]");
        wcsncpy(word[i], words->data[i]->data, 100);
    }
    for(size_t _ = 3; _ < (1 + words->size); ++_){
        wchar_t* curline_wc = (wchar_t*)malloc(sizeof(wchar_t) * 500);
        char* curline = (char*)malloc(sizeof(char) * 500);
        if(curline_wc == NULL) printError(L"Failed to allocate memory for the curline_wc [fn: is_happened]");
        if(curline == NULL) printError(L"Failed to allocate memory for the curline [fn: is_happened]");
        size_t len123 = words->data[_-3]->size + words->data[_-2]->size + words->data[_-1]->size;
        wcsncpy(curline_wc, wcsncat(word[0], wcsncat(word[1], word[2], 200), 300), 500);
        size_t check_len = wcstombs(curline, curline_wc, 500);
        if(check_len) curline[len123] = L'\0';
        if(flag == 2 && strptime(curline, "%d%b%Y", time_info)){
            strftime(curline, 500, "%d.%m.%Y", time_info);
            if((mktime(time_info) - current_time) < 0){
                wprintf(L"%s Happened\n", curline);
            } else {
                wprintf(L"%s Not Happened\n", curline);
            }
            flag = 0;
        } else {
            if(flag < 2) flag++;
        }
        if(_ != words->size){
            for(u8 i = 0; i < 3; ++i){
                wcsncpy(word[i], words->data[_+i-2]->data, 100);
            }
        }
        free(curline_wc);
        free(curline);
    }
    for(u8 i = 0; i < 3; ++i){
        free(word[i]);
    }
    free(word);
    free(time_info);
}
