#include "Common.h"
#include "Function1.h"
#include "Function2.h"
#include "Function3.h"
#include "Function9.h"
#include "SortFunctions.h"
#include "Output.h"
#include "Input.h"
#include "FreeMemory.h"

int main() {
    printf("Course work for option 4.12, created by Rustam Abdusalamov.\n");
    int opt;
    if (scanf("%d", &opt) == 0)
    {
        printf("Error: Введено не число! Программа будет завершена.\n");
        return 0;
    }
    if (opt == 5) {
        PrintInfo();
        return 0;
    }
    int sentences_count;
    char** text = ReadText(&sentences_count);
    if (!sentences_count) {
        printf("Error: Пользователем не был введён текст!\n");
        return 0;
    }
    switch (opt) {
        case 0:
            PrintText(text, sentences_count);
            break;
        case 1:
            text = Function1(text, &sentences_count);
            PrintText(text, sentences_count);
            break;
        case 2:
            Function2(text, sentences_count);
            PrintText(text, sentences_count);
            break;
        case 3:
            text = Function3(text, &sentences_count);
            PrintText(text, sentences_count);
            break;
        case 4:
            qsort(text, sentences_count, sizeof(char*), compare);
            PrintText(text, sentences_count);
            break;
        case 9:
            Function9(text,sentences_count);
            break;
        default:
            printf("Error. Операции не существует! Программа будет завершена.\n");
            break;
    }
    FreeMemory(text, sentences_count);
    return 0;
}
