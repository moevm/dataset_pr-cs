#include "fill_and_firstprocc_structure.h"


int strcmp_withoutreg(const wchar *sent1, const wchar *sent2)
{
    for (;; sent1++, sent2++)
    {
        int result = towlower(*sent1) - towlower(*sent2);
        if (result != 0 || !*sent1)
            return result;
    }
    return 0;
}

int already_in(wchar **const arrofsents, wchar const *sent, unsigned countsents)
{
    if (countsents == 0) return 1;

    for (int i = 0; i < countsents; i++)
    {
        if (wcslen(arrofsents[i]) != wcslen(sent)) continue;
        if (strcmp_withoutreg(arrofsents[i], sent) == 0) return 0;
    }
    return 1;
}

void search_seps(wchar *sentence, Text *structure)
{
    structure->arrofsents[structure->countsents]->arrofseps = malloc(sizeof(wchar));

    if (structure->arrofsents[structure->countsents]->arrofseps == NULL) {
        wprintf(L"Error: ошибка выделения памяти для массива разделителей\n");
        exit(0);
    }

    unsigned countseps = 0;
    for (int i = 0; i < wcslen(sentence); i++)
    {
        if (sentence[i] == L',' && sentence[i + 1] == L' ')
        {
            structure->arrofsents[structure->countsents]->arrofseps[countseps++] = L'!';
            i += 1;
        }
        else if (sentence[i] == L',' || sentence[i] == L' ')
        {
            structure->arrofsents[structure->countsents]->arrofseps[countseps++] = sentence[i];
        }
        structure->arrofsents[structure->countsents]->arrofseps = realloc(structure->arrofsents[structure->countsents]->arrofseps, sizeof(wchar) * (countseps + 1));

        if (structure->arrofsents[structure->countsents]->arrofseps == NULL) {
            wprintf(L"Error: ошибка перераспределения памяти для массива разделителей\n");
            exit(0);
        }

    }
    structure->arrofsents[structure->countsents]->countseps = countseps;
}


void fill_and_firstprocc_struct(Text *structure)
{
    structure->arrofsents = malloc(sizeof(Sentence *));

    if (structure->arrofsents == NULL) {
        wprintf(L"Error: ошибка выделения памяти для массива указателей на структуры Sentence\n");
        exit(0);
    }

    wchar **sentences = malloc(sizeof(wchar *));

    if (sentences == NULL) {
        wprintf(L"Error: ошибка выделения памяти для массива указателей sentence\n");
        exit(0);
    }
    
    wchar prevchar;
    unsigned countn = 0;

    while (1)
    {
        wchar *sent = malloc(sizeof(wchar));

        if (sent == NULL) {
            wprintf(L"Error: ошибка выделения памяти для указателя sent\n");
            exit(0);
        }

        unsigned countchars = 0;
        wchar ch = L'\0';
        while (ch != L'.' && countn != 2)
        {
            prevchar = ch;
            ch = getwchar();

            if (ch == L'.') continue;

            if ((ch == L' ' || ch == L'\t') && countchars == 0) continue;
            if (prevchar == L' ' && ch == L' ') continue;

            if (prevchar != L'\n' && ch == L'\n') continue;

            if (prevchar == L'\n' && ch == L'\n')
            {
                countn += 2;
                continue;
            }

            sent[countchars++] = ch;
            sent = realloc(sent, (countchars + 1) * sizeof(wchar));

            if (sent == NULL) {
                wprintf(L"Error: ошибка перераспределения памяти для указателя sent\n");
                exit(0);
            }

        }
        sent[countchars] = '\0';

        if(structure->countsents == 0 && countn == 2 && countchars == 0){
            wprintf(L"Error: ошибка ввода текстовых данных. Введите текст!\n");
            exit(0);
        }

        if (countn == 2 && countchars == 0)
        {
            free(sent);
            break;
        }

        if (already_in(sentences, sent, structure->countsents)) 
        {
            structure->arrofsents[structure->countsents] = malloc(sizeof(Sentence));

            if (structure->arrofsents[structure->countsents] == NULL) {
                wprintf(L"Error: ошибка выделения памяти для структуры Sentence\n");
                exit(0);
            }

            search_seps(sent, structure);
            structure->arrofsents[structure->countsents]->sentlen = countchars;
            sentences[structure->countsents++] = sent;
            sentences = realloc(sentences, sizeof(wchar *) * (structure->countsents + 1));
            structure->arrofsents = realloc(structure->arrofsents, (structure->countsents + 1) * sizeof(Sentence *));

            if (structure->arrofsents == NULL) {
                wprintf(L"Error: ошибка перераспределения памяти для массива указателей на структуры Sentence\n");
                exit(0);
            }

        }
        else
        {
            free(sent);
        }
    }
    for (int i = 0; i < structure->countsents; i++)
    {
        unsigned countwords = 0;
        structure->arrofsents[i]->arrofwords = malloc(sizeof(wchar *));

        if (structure->arrofsents[i]->arrofwords == NULL) {
            wprintf(L"Error: ошибка выделения памяти для массива указателей на слова\n");
            exit(0);
        }

        wchar *pt;
        wchar *pch = wcstok(sentences[i], L" ,", &pt);
        while (pch != NULL)
        {
            structure->arrofsents[i]->arrofwords[countwords] = pch;
            countwords++;
            pch = wcstok(NULL, L" ,", &pt);
            structure->arrofsents[i]->arrofwords = realloc(structure->arrofsents[i]->arrofwords, sizeof(wchar *) * (countwords + 1));

            if (structure->arrofsents[i]->arrofwords == NULL) {
                wprintf(L"Error: ошибка перераспределения памяти для массива указателей на слова\n");
                exit(0);
            }

        }
        structure->arrofsents[i]->countwords = countwords;
        free(pt);
        free(pch);
    }
    free(sentences);
}
