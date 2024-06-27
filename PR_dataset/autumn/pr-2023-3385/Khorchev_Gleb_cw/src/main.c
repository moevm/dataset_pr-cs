#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <wchar.h>
#include "input_functions.h"
#include "help_functions.h"
#include "struct.h"
#include "func_1.h"
#include "func_2.h"
#include "func_4.h"
#include "func_9.h"

int main()
{
    setlocale(LC_CTYPE, "");
    wprintf(L"Course work for option 5.9, created by Gleb Khorchev.\n");
    int command;
    wchar_t s;
    wscanf(L"%d%lc", &command, &s);
    switch(command)
    {
        case 0:{
            text text_exp = read_text();
            for( size_t i=0; i<text_exp.lenght; i++)
            {
                for (size_t j=0; j< text_exp.sentences[i]->word_count; j++)
                {
                    for(size_t k=0; k<wcslen(text_exp.sentences[i]->words[j]); k++){
                        if ( j == 0 && text_exp.sentences[i]->words[j][k] == '\n' ){}
                        else  wprintf(L"%lc", text_exp.sentences[i]->words[j][k]);}
                }
                wprintf(L"\n");
            }
            free_text(text_exp);
            break;
        }
        case 1:{
            text text_exp = read_text();
            text_exp = change_tca_tcia(text_exp);
            for( size_t i=0; i<text_exp.lenght; i++)
            {
                for (size_t j=0; j< text_exp.sentences[i]->word_count; j++)
                {
                    for(size_t k=0; k<wcslen(text_exp.sentences[i]->words[j]); k++){
                        if ( j == 0 && text_exp.sentences[i]->words[j][k] == '\n' ){}
                        else  wprintf(L"%lc", text_exp.sentences[i]->words[j][k]);}
                }
                wprintf(L"\n");
            }

            free_text(text_exp);
            break;
        }
        case 2:{
            text text_exp = read_text();
            pr_sec_w_in_f_sen(text_exp);
            free_text(text_exp);
            break;
        }
        case 3:{
            text text_exp = read_text();
            qsort(text_exp.sentences, text_exp.lenght, sizeof(sentence*), compare);
            for( size_t i=0; i<text_exp.lenght; i++)
            {
                for (size_t j=0; j< text_exp.sentences[i]->word_count; j++)
                {
                    for(size_t k=0; k<wcslen(text_exp.sentences[i]->words[j]); k++){
                        if ( j == 0 && text_exp.sentences[i]->words[j][k] == '\n' ){}
                        else  wprintf(L"%lc", text_exp.sentences[i]->words[j][k]);}
                }
                wprintf(L"\n");
            }

            free_text(text_exp);
            break;
        }
        case 4:{
            text text_exp = read_text();
            text_exp = del_more_then_10_w(text_exp);
            for( size_t i=0; i<text_exp.lenght; i++)
            {
                for (size_t j=0; j< text_exp.sentences[i]->word_count; j++)
                {
                    for(size_t k=0; k<wcslen(text_exp.sentences[i]->words[j]); k++){
                        if ( j == 0 && text_exp.sentences[i]->words[j][k] == '\n' ){}
                        else  wprintf(L"%lc", text_exp.sentences[i]->words[j][k]);}
                }
                wprintf(L"\n");
            }

            free_text(text_exp);
            break;
        }
        case 5:{
            wprintf(L"0–Вывод текста после первичной обязательной обработки.\n1-Заменить ться на тся и наоборот.\n2-Вывести все предложения,в которых встречается второе слово первого предложеия. Само слово вывести зеленым цыетом.\n3-Отсортировать предложения по возрастанию количества.\n4-Удалить все предложения, содержащие более 10 слов.\n");
            break;
        }
        case 9:{
            wchar_t* str = (wchar_t*)malloc(sizeof(wchar_t*)*100);
            wscanf(L"%ls", str);
            text text_exp = read_text();
            f_9(text_exp, str);
            break;
        }
        default:{
            wprintf(L"Введены неверные денные");
            return 1;
        }
    }
    return 0;
}

