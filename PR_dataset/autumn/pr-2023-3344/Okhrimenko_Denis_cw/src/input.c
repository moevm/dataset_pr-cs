#include "input.h"

sentence_t* read_sentence()
{
    sentence_t* line = (sentence_t*)malloc(sizeof(sentence_t));
    if(line == NULL) printError(L"Failed to allocate memory for the struct sentence_t*");
    line->data = (wchar_t*)malloc(sizeof(wchar_t));
    if(line->data == NULL) printError(L"Failed to allocate memory for the sentence.");
    line->size = 0;
    wchar_t c;
    size_t capacity = 1;
    u8 break_flag = 2;
    int top = 0;
    while((c = getwchar()) != WEOF){
        if(c == L'\n'){
            break_flag--;
        } else {
            break_flag = 2;
        }
        if(!break_flag){
            line->data = NULL;
            return line;
        }
        if(line->size > 0 || !iswspace(c))
            line->data[line->size++] = c;
        if(c == L'.'){
            break;
        }
        if(capacity <= line->size){
            capacity *= MUL_MEM;
            line->data = (wchar_t*)realloc(line->data, sizeof(wchar_t) * capacity);
            if(line->data == NULL) printError(L"Failed to reallocate memory for the sentence");
        }
    }
    line->data = (wchar_t*)realloc(line->data, sizeof(wchar_t) * (1 + line->size));
    if(line->data == NULL) printError(L"Failed to reallocate memory for the sentence");
    line->data[line->size] = L'\0';
    return line;
}

text_t* read_text()
{
    sentence_t** lines = (sentence_t**)malloc(sizeof(sentence_t*));
    if(lines == NULL) printError(L"Failed to allocate memory for the struct sentence_t**");
    size_t top_txt = 0;
    while((lines[top_txt] = read_sentence())->data != NULL){
        u8 flag = 1;
        for(size_t i = 0; i < top_txt; ++i){
            if(!wcscmp(lines[top_txt]->data, lines[i]->data)) flag = 0;
        }
        if(flag){
            top_txt++;
            lines = (sentence_t**)realloc(lines, (sizeof(sentence_t*) * (top_txt + 1)));
            if(lines == NULL) printError(L"Failed to reallocate memory for the struct sentence_t**");
        } else {
            free(lines[top_txt]->data);
        }
    }
    text_t* result = (text_t*)malloc(sizeof(text_t));
    if(result == NULL) printError(L"Failed to allocate memory for the struct text_t* text");
    result->data = lines;
    result->size = top_txt;
    return result;
}
