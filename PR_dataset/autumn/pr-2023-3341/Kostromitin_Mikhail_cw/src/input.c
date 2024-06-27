#include "input.h"


void input(Text* text)
{
    wchar_t symbol;

    int flagN = 1;
    int flagExit = 0;

    text->sentences[text->size].len = 0;
    text->sentences[text->size].sizeOfBuf = SENTENCESIZE;

    while ((symbol = getwchar()) != WEOF)
    {
        if (flagExit) 
        {
            if (text->sentences[text->size].len) insertSymbol(text, L'.', &flagN);
            break;
        }

        if (!(text->sentences[text->size].len)) 
        {      
            wchar_t bufSymb = deleteSpaces(symbol, &flagN);
            if (bufSymb != L'\0') 
            {
                text->sentences[text->size].sentence = (wchar_t*)malloc(sizeof(wchar_t) * text->sentences[text->size].sizeOfBuf);

                insertSymbol(text, bufSymb, &flagN);
                continue;
            } else
            {
                if (!flagN) break;
                insertSymbol(text, symbol, &flagN);
                continue;
            }
        }

        switch(symbol)
        {
            case(L'\n'):
            {
                if (!flagN) flagExit = 1;
                insertSymbol(text, symbol, &flagN);

                break;
            }
            default:
            {
                insertSymbol(text, symbol, &flagN);
            }
        }

        if (flagExit) 
        {
            if (text->sentences[text->size].len) insertSymbol(text, L'.', &flagN);
            break;
        }
    }
}


void insertSymbol(Text* text, wchar_t symbol, int* flagN)
{
    if (text->sentences[text->size].len >= (text->sentences[text->size].sizeOfBuf - 2))
    {
        text->sentences[text->size].sizeOfBuf *= 2;
        wchar_t* buf = (wchar_t*)realloc(text->sentences[text->size].sentence, sizeof(wchar_t) * (text->sentences[text->size].sizeOfBuf));
        text->sentences[text->size].sentence = buf;
    }

    if (symbol != L'\n') 
    {
        text->sentences[text->size].sentence[(text->sentences[text->size].len)++] = symbol;
        *flagN = 1;
    }
    else *flagN = 0;

    if (symbol == L'.')
    {
        text->sentences[text->size].sentence[(text->sentences[text->size].len)++] = L'\n';
        text->sentences[text->size].sentence[text->sentences[text->size].len] = L'\0';

        (text->size)++;
        text->sentences[text->size].len = 0;
        text->sentences[text->size].sizeOfBuf = SENTENCESIZE;

        if (text->size >= (text->sizeOfBuf - 1))
        {
            text->sizeOfBuf *= 2;
            Sentence* buf = (Sentence*)realloc(text->sentences, sizeof(Sentence) * (text->sizeOfBuf));
            text->sentences = buf;
        }
    }
}


wchar_t deleteSpaces(wchar_t bufSymbol, int* flagN)
{
    while (iswblank(bufSymbol))
    {
        bufSymbol = getwchar();
        *flagN = 1;
    }
    if (bufSymbol != L'\n') return bufSymbol;

    return L'\0';
}


int firstInputOutput(Text* text)
{
    int num = -1;
    
    wprintf(L"Course work for option 5.3, created by Mikhail Kostromitin.\n");

    if (!wscanf(L"%d", &num)) 
    {
        wprintf(L"Error: Не удалось считать число.\n");
        return 1;
    }

    switch (num)
    {
        case(0):
        {
            input(text);
            firstProc(text);
            return 0;
        }
        case(1):
        {
            input(text);
            firstProc(text);
            maskOfSent(text);
            return 0;
        }
        case(2):
        {
            input(text);
            firstProc(text);
            capitalStart(text);
            return 0;
        }
        case(3):
        {
            input(text);
            firstProc(text);
            sortByNumOfVowel(text);
            return 0;
        }
        case(4):
        {
            input(text);
            firstProc(text);
            numberOfRepeatWords(text);
            return 0;
        }
        case(5):
        {
            wprintf(L"Программа реализует следущий набор функций:\n");
            wprintf(L"0 - Первичная обработка текста: удаление всех повторяющихся предложений.\n");
            wprintf(L"1 - Для каждого предложения вывод строки образца, удовлетворяющей каждому слову в предложении.\n");
            wprintf(L"2 - Удаление всех предложений, в которых нет заглавных букв в начале слова.\n");
            wprintf(L"3 - Сортировка слов в предложении по количеству гласных букв.\n");
            wprintf(L"4 - Вывод для каждого предложения количества одинаковых слов.\n");
            wprintf(L"5 - Вывод справки о функциях, которые реализует программа.\n");
            return 1;
        }
        case (9):
        {
            Sentence* firstSent = firstInp();
            input(text);
            firstProc(text);
            certainWords(text, firstSent);
            return 0;
        }
        default:
        {
            wprintf(L"Error: Число не принадлежит отрезку от 0 до 5.\n");
            return 1;
        }
    }

}


Sentence* firstInp()
{
    Sentence* string = (Sentence*)malloc(sizeof(Sentence));
    string->sizeOfBuf = 100;
    string->len = 0;
    string->sentence = (wchar_t*)malloc(sizeof(wchar_t) * string->sizeOfBuf);
    wchar_t symbol = getwchar();
    

    while (iswspace(symbol))
    {
        symbol = getwchar();
        continue;
    }

    while (symbol != L'\n')
    {
        if (string->len + 2 >= string->sizeOfBuf)
        {
            string->sizeOfBuf *= 2;
            wchar_t* buf = (wchar_t*)realloc(string->sentence, sizeof(wchar_t) * string->sizeOfBuf);
            string->sentence = buf;
        }

        string->sentence[(string->len)++] = symbol;
        symbol = getwchar();
    }
    string->sentence[string->len++] = L'\n';
    string->sentence[string->len] = L'\0';

    return string;
}
