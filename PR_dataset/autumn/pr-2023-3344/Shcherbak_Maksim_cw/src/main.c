#include <stdlib.h>
#include <locale.h>
#include <wchar.h>

#include "structures.h"
#include "printFunctions.h"
#include "inputHandler.h"
#include "back.h"
#include "date.h"
#include "sorting.h"
#include "deleting.h"
#include "dop.h"

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
        printArray(&sentencesArray);
        break;
    case 1:
        wrapper(data, &sentencesArray);
        printArray(&sentencesArray);
        break;
    case 2:
        wrapper(back, &sentencesArray);
        printArray(&sentencesArray);
        break;
    case 3:
        wrapper(sortLetters, &sentencesArray);
        printArray(&sentencesArray);
        break;
    case 4:
        wrapper(delete, &sentencesArray);
        printArray(&sentencesArray);
        break;
    case 5:
        printOptions();
        break; 
    case 8:
        wrapper(palindromInText, &sentencesArray);
        break;     
    default:
        wprintf(L"ERROR: incorrect input data. Please use numbers from 0 to 5\n");
        wprintf(L"Program competed unsuccsessfully\n");
        wprintf(L"Error: Несуществующий номер команды, введите 5 для отображения функционала программы\n");
        return 0;
    }

    //printArray(&sentencesArray);

    return 0;

}
