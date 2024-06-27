#include "../include/main.h"

int main() {
    setlocale(LC_ALL,"");
    wprintf(L"Course work for option 5.3, created by Nikita Pivoev.\n");
    int task = -1;
    wscanf(L"%d", &task);

    switch (task){
    case 0: printText(getText(task));
        break;
    case 1: findMask(getText(task));
        break;
    case 2: printText(removeLowerCaseSentences(getText(task)));
        break;
    case 3: sortWords(getText(task));
        break;
    case 4: printSameWords(getText(task));
        break;
    case 5: wprintf(L"%s\n%s\n%s\n%s\n%s\n%s\n",
                "0 - Вывод отредактированного текста.",
                "1 - Составление масок для каждого предложения.",
                "2 - Исключение предложений, в которых нет заглавных букв в начале слова.",
                "3 - Сортировка слов в предложениях по числу гласных букв.",
                "4 - Вывод числа одинаковых слов в предложениях.",
                "5 - Вывод справочной информации.");
        break;
    case 9: printText(newTask(getText(task)));
        break;
    default: wprintf(L"Error: wrong task input.\n");
        break;
    }

    return 0;
}