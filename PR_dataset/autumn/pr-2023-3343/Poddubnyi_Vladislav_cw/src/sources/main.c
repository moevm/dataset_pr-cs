//
// Created by rect on 15.11.2023.
//

#include "../include/main.h"

#define LOCALE ""

int main() {
    setlocale(LC_ALL, LOCALE);
    wprintf(L"Course work for option 5.7, created by Vladislav Poddubnyi.\n");
    switch (getChoice()) {
        case 0:
            printText(getText());
            break;
        case 1:
            printText(getColored(getText()));
            break;
        case 2:
            printText(getUpperCaseWords(getText()));
            break;
        case 3:
            printText(getSorted(getText()));
            break;
        case 4:
            printText(getWithoutNums(getText()));
            break;
        case 5:
            wprintf(L"0 – вывод текста после первичной обязательной обработки (если предусмотрена заданием данного уровня сложности).\n"
                    "1 – “Раскрасить” каждое слово в зависимости от остатка от деления его длины на 4. Если остаток равен 0 - красный цвет, 1 - синий, 2 - зеленый, 3 - желтый.\n"
                    "2 – Распечатать каждое слово, которое начинается и заканчивается на заглавную букву, и номера предложений, в которых оно встречается .\n"
                    "3 – Отсортировать предложения по длине последнего слова в предложении.\n"
                    "4 – Удалить все числа из предложений. Число - набор подряд идущих цифр, перед и после которого стоят пробелы.\n"
                    "5 – вывод справки о функциях, которые реализует программа.\n");
            break;
        case 9:
            printText(getWithDupWords(getText()));
            break;
        default:
            fwprintf(stderr, L"Error: Incorrect function. Input 5 for list of functions.\n");
    }
    return 0;
}
