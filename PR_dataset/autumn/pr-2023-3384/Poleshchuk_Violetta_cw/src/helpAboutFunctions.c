#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include "header_files/helpAboutFunctions.h"

void outputPrint(){
    setlocale(LC_ALL, "");
    wprintf(L"0 – вывод текста после первичной обязательной обработки (если предусмотрена заданием данного уровня сложности)\n");
    wprintf(L"1 – вызов функции под номером 1 из списка задания\n");
    wprintf(L"2 – вызов функции под номером 2 из списка задания\n");
    wprintf(L"3 – вызов функции под номером 3 из списка задания\n");
    wprintf(L"4 – вызов функции под номером 4 из списка задания\n");
    wprintf(L"5 – вывод справки о функциях, которые реализует программа.\n");
}
