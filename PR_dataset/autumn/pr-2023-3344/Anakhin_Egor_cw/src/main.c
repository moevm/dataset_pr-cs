#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

#include "structures.h"
#include "printFunctions.h"
#include "inputHandler.h"
#include "palindromsFinder.h"
#include "replacingSpecSymbols.h"
#include "sorting.h"
#include "deleting.h"
#include "new_func.h"


int main() {

    // Основная функция. Инициализирует структуру и вызывает функцию, которую выбрал пользователь. После всех преобразовний со структурой выводит ее.

    setlocale(LC_CTYPE, "");

    struct Text sentencesArray;
    sentencesArray.len = 0;
    sentencesArray.sentences = malloc(2 * sizeof(struct Sentence*));

    int option = start();

    int leng;

    wchar_t *word;
    wchar_t *new_text;

    switch (option) {
    case 0:
        wrapper(0, &sentencesArray);
        break;
    case 1:
        wrapper(palindromsInText, &sentencesArray);
        return 0;
    case 2:
        wrapper(replaceSpecialSymbols, &sentencesArray);
        break;
    case 3:
        wrapper(sortLetters, &sentencesArray);
        break;
    case 4:
        wrapper(deleteDifferentLanguages, &sentencesArray);
        break;
    case 5:
        printOptions();
        break;
    case 9:
        // wrapper(new_func, &sentencesArray, );
        // return 0;
        wscanf(L"%ls\n", word, 100);
        leng = wcslen(word);

        new_text = reading();

        addSentencesToText(&sentencesArray, new_text);
        deleteWhiteSpaces(&sentencesArray);
        new_func(&sentencesArray, leng);
        return 0;   
    default:
        printError(L"ERROR: incorrect input data. Please use numbers from 0 to 5\n");
        printError(L"Program competed unsuccsessfully\n");
        return 1;
    }

    printArray(&sentencesArray);

    return 0;

}