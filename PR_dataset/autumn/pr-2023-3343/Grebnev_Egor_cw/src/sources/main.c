#include <locale.h>
#include <wctype.h>
#include "log.h"
#include "txtprocessing.h"
#include "counting.h"
#include "sorting.h"
#include "timeprocessing.h"

#define SENTENCE_SPLITTERS L".?!;"
#define LANGUAGE_LOCALE ""

void printHelp(void);
void processInput(void);
void userInputProcessing(int nextMove, Text *text);

int main(void)
{
    setlocale(LC_ALL, LANGUAGE_LOCALE);

    logInfo(L"%s", "Course work for option 5.11, created by Egor Grebnev.");
    processInput();
    return 0;
}
void processInput(void)
{
    wint_t charMove = getwchar();

    if (iswdigit(charMove))
    {
        int intMove = (int)charMove - L'0';
        if (intMove != 5)
        {
            Text *text = createTextStruct(SENTENCE_SPLITTERS);
            userInputProcessing(intMove, text);
            freeText(text);
            return;
        }
        printHelp();
        return;
    }

    logErr(L"%s", "Write the digit of the function");
}
void userInputProcessing(int nextMove, Text *text)
{
    switch (nextMove)
    {
    case 0:
        printText(text);
        break;
    case 1:
        findTimeInSentences(text);
        break;
    case 2:
        removeUpperCaseLettersText(text);
        printText(text);
        break;
    case 3:
        sortTextByCyrillic(text);
        printText(text);
        break;
    case 4:
        removeWithoutSpecialChars(text);
        printText(text);
        break;
    case 9:
        duplicateWords(text);
        printText(text);
        break;
    default:
        logErr(L"%s", "Undefined function, try 0-5");
        break;
    }
}

void printHelp(void)
{
#ifdef LOG_USE_COLOR
    logInfoDefault(L"\033[1;36mСправка по функциям:\033[0m");
    logInfoDefault(L"\033[1;33m0. Базовый вывод\033[0m - \033[1;37mвывод текста после первичной обязательной обработки.\033[0m");
    logInfoDefault(L"\033[1;33m1. Поиск подстроки по формату\033[0m - \033[1;37mДля каждой подстроки в тексте, задающей время вида “часы:минуты”, вывести номер предложения в котором она  встречается и количество минут до текущего времени (время, в которое начала выполняться данная задача).\033[0m");
    logInfoDefault(L"\033[1;33m2. Удаление заглавных букв\033[0m - \033[1;37mВ каждом предложении удалить все заглавные латинские буквы.\033[0m");
    logInfoDefault(L"\033[1;33m3. Сортировка\033[0m - \033[1;37mОтсортировать предложения по уменьшению количеству кириллических букв.\033[0m");
    logInfoDefault(L"\033[1;33m4. Удаление предложений\033[0m - \033[1;37mУдалить все предложения в которых нет специальных символов.\033[0m");
    logInfoDefault(L"\033[1;33m5. Справка\033[0m - \033[1;37mВывод справки по функциям.\033[0m");
#else
    logInfoDefault(L"Справка по функциям:");
    logInfoDefault(L"0. Базовый вывод - вывод текста после первичной обязательной обработки.");
    logInfoDefault(L"1. Поиск подстроки по формату - Для каждой подстроки в тексте, задающей время вида “часы:минуты”, вывести номер предложения в котором она  встречается и количество минут до текущего времени (время, в которое начала выполняться данная задача).");
    logInfoDefault(L"2. Удаление заглавных букв - В каждом предложении удалить все заглавные латинские буквы.");
    logInfoDefault(L"3. Сортировка - Отсортировать предложения по уменьшению количеству кириллических букв.");
    logInfoDefault(L"4. Удаление предложений - Удалить все предложения в которых нет специальных символов.");
    logInfoDefault(L"5. Справка - Вывод справки по функциям.");
#endif
}
