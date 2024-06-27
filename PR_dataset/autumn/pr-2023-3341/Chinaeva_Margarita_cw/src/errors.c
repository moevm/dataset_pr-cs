#define _CRT_SECURE_NO_WARNINGS 

#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <locale.h>

enum error_list { OPTION_ERROR, END_DOT, VOID_STR, VOID_TEXT };

void error(int type) {
    switch (type)
    {
    case OPTION_ERROR:
        wprintf(L"Error: нет команды с таким номером\n");
        break;
    case END_DOT:
        wprintf(L"Error: последнее предложение не заканчивается точкой\n");
        break;
    case VOID_STR:
        wprintf(L"Error: введено пустое предложение\n");
        break;
    case VOID_TEXT:
        wprintf(L"Error: текст не был введен\n");
        break;
    }
}

