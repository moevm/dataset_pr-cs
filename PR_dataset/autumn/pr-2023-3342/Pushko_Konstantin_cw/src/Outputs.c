#include"Structs.h"
#include"Outputs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
void inquiry_output()
{
    wprintf(L"Справка о программе:\n");
    wprintf(L"0 – Вывод текста после первичной обязательной обработки\n");
    wprintf(L"1 – Распечатать каждое слово (с учётом регистра) и количество его повторений в тексте.\n");
    wprintf(L"2 – Заменить каждый символ, который не является буквой, на его код.\n");
    wprintf(L"3 – Отсортировать предложения по количеству латинских букв в предложении.\n");
    wprintf(L"4 – Удалить все предложения, которые содержат специальные символы и не содержат заглавные буквы. К специальным символам относятся: #$^%@.\n");
    wprintf(L"5 – Вывод справки о программе.\n");
}
void output(struct Text text)
{

    for (size_t i = 0; i < text.sentences_count; i++)
    {
        for (size_t j = 0; j < text.sentences[i].words_count; j++)
        {
            if (j == text.sentences[i].words_count - 1)
            {
                wprintf(L"%ls\n", text.sentences[i].words[j].letters);
            }
            else
            {
                wprintf(L"%ls ", text.sentences[i].words[j].letters);
            }
        }
        
    }
}