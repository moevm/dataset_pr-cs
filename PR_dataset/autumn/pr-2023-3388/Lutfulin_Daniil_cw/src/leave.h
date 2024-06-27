#pragma once
#include <wchar.h>
#include <stdlib.h>
#include "structs.h"
#define MEM_ERROR L"Error: Не удалось выделить память"
#define CHOOSE_FUNC_ERROR L"Error: Выбран неверный номер функции"
#define INPUT_ERROR L"Error: Некорректный ввод, текст должен заканчиваться двумя идущими подряд символами переноса строки"

void leave(wchar_t*);
void free_text(Text *text);