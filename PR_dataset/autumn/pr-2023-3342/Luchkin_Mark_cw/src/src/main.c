#include "main.h"


int main() {
    setlocale(LC_ALL, "");

    printCwInfo();

    switch (getCommand()){
        case 0:
        printText(inputText());
        break;

        case 1: {
            wchar_t *pattern = getPattern();
            Text inputTextToMatch = inputText();
            printByPattern(inputTextToMatch, pattern);
            break;
        }
        case 2: {
            Text inputToSortSentences = inputText();
            sortSentences(&inputToSortSentences);
            printText(inputToSortSentences);
            break;
        }
        case 3: {
            Text inputToSortWords = inputText();
            sortWords(&inputToSortWords);
            printText(inputToSortWords);
            break;
        }
        case 4:
        printNeededSentences(inputText());
        break;
        case 5:

        wprintf(L"0 - Вывод текста после первичной обязательной обработки (если предусмотрена заданием данного уровня сложности).\n"
                "1 - Вывод всех предложения, в которых каждое слово удовлетворяет введенной строке-условию.\n"
                "2 - Отсортировать предложения по средней длине слов в предложении.\n"
                "3 - Преобразовать предложения так, чтобы слова располагались в порядке уменьшения длины слова.\n"
                "4 - Удалить все предложения, в котором больше 5 или меньше 2 слов.\n"
                "5 - Вывод справки о функциях, которые реализует программа.\n");
        break;
        case 9: {
            wchar_t* frstWord = getFirstWord();
            Text inputtedText = inputText();
            isSameLetters(inputtedText, frstWord);
            break;
        }
        
        default:
        wprintf(L"Error: Incorrect command. Input 5 to see the list of functions.\n");
    }

    return 0;
}
