#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <stdio.h>

int start(){
    wprintf(L"Course work for option 5.7, created by Klyukin Alexander.\n");
    int option = 0;
    wscanf(L"%lc", &option);
    getwchar();
    return option;
}

void info(){
    wprintf(L"1 - “Раскрасить” каждое слово в зависимости от остатка от деления его длины на 4. Если остаток равен 0 - красный цвет, 1 - синий, 2 - зеленый, 3 - желтый.\n");
    wprintf(L"2 - Распечатать каждое слово, которое начинается и заканчивается на заглавную букву, и номера предложений, в которых оно встречается.\n");
    wprintf(L"3 - Отсортировать предложения по длине последнего слова в предложении.\n");
    wprintf(L"4 - Удалить все числа из предложений. Число - набор подряд идущих цифр, перед и после которого стоят пробелы.\n");
    wprintf(L"5 - Справка о функциях.\n");
}
