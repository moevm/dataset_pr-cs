#include "delete_repeatChar.h"


void delete_repeatChar(Text *structure)
{
    unsigned len_oldword = 0;
    for (int i = 0; i < structure->countsents; i++)
    {
        for (int j = 0; j < structure->arrofsents[i]->countwords; j++)
        {
            unsigned countrepeats = 0;
            unsigned count_newchars = 0;
            len_oldword = wcslen(structure->arrofsents[i]->arrofwords[j]);
            wchar *newword = malloc(sizeof(wchar));

            if (newword == NULL) {
                wprintf(L"Error: ошибка выделения памяти для слова без повторяющихся символов\n");
                exit(0);
            }

            wchar prevchar = L'\0';
            for (int k = 0; k < len_oldword; k++)
            {
                if (prevchar == structure->arrofsents[i]->arrofwords[j][k])
                {
                    countrepeats++;
                }
                else
                {
                    countrepeats = 0;
                }
                if (countrepeats == 0)
                {
                    newword[count_newchars++] = structure->arrofsents[i]->arrofwords[j][k];
                    newword = realloc(newword, sizeof(wchar) * (count_newchars + 1));

                    if (newword == NULL) {
                        wprintf(L"Error: ошибка перераспределения памяти для слова без повторяющихся символов\n");
                        exit(0);
                    }

                }
                prevchar = structure->arrofsents[i]->arrofwords[j][k];
            }
            newword[count_newchars] = L'\0';
            if (len_oldword != wcslen(newword))
            {
                wmemmove(structure->arrofsents[i]->arrofwords[j], newword, count_newchars + 1);
                free(newword);
            }
            else
            {
                free(newword);
            }
        }
    }
}
