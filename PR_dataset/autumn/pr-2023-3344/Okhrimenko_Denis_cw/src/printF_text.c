#include "printF_text.h"

void printError(wchar_t* lineError)
{
    wprintf(L"Error: <%ls>\n", lineError);
    exit(0);
}

void cleanUpMemory(text_t* text)
{
    for(size_t i = 0; i < text->size; ++i){
        free(text->data[i]->data);
        free(text->data[i]);
    }
    free(text->data);
    free(text);
}

void printF_text(text_t* text)
{
    for(size_t i = 0; i < text->size; ++i){
        wprintf(L"%ls\n", text->data[i]->data);
    } 
}

void printOptions()
{
    wprintf(L"Справочный материал:\n  Введите 0 для вывода текста после первичной обязательной обработки.\n  Введите 1 для замены в тексте всех подстрок “high noon” на “полдень” и “полночь” на “midnight”.\n  Введите 2 для вывода всех дат в тексте, заданных в виде “DD/MM/YYYY” или “YYYY-MM-DD”, в порядке возрастания этих дат.\n  Введите 3 для удаления всех предложений, которые начинаются и заканчиваются одним и тем же словом.\n  Введите 4 для вывода всех вхождений дат в тексте вида “<day> <month> <year>” этих дат в виде: <day>.<month>.<year>.\n");
}
