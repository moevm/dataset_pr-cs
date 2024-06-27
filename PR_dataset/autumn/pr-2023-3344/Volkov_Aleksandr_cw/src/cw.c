#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <stdio.h>
#include "ioFunc.h"
#include "processFunc.h"


int main()
{
    setlocale(LC_CTYPE, ""); // Устанавливаем локаль
    wprintf(L"Course work for option 5.1, created by Volkov Aleksandr\n");
    wchar_t define_action;
    wchar_t input[5];
    // Считываем ввод пользователя
    fgetws(input, 5, stdin);
    if (wcslen(input) > 2) {
    define_action = L'q';
    } else {
    define_action = input[0];
    }
    struct Text my_text;
    int status;
    int res;
    int flag;
    wchar_t *word1;
    wchar_t *word2;
    wchar_t *str;
    int dec;
    // В зависимости от выбранного действия выполняется опеределённая операция
    switch (define_action) {
        case L'0':
            my_text = readText();
            if (my_text.text == NULL) {
                if (my_text.count == -1)
                    wprintf(L"Error: Ошибка выделения памяти.\n");
                if (my_text.count == 0)
                    wprintf(L"Error: Не введено ни одного предложения.\n");
                exit(1);
            }
            status = removeRepeated(&my_text);
            if (status < 0) {
                wprintf(L"Error: Ошибка выделения памяти.\n");
                exit(1);
            }
            printText(&my_text);
            freeText(&my_text);
            break;
        case L'1':
            my_text = readText();
            if (my_text.text == NULL) {
                if (my_text.count == -1)
                    wprintf(L"Error: Ошибка выделения памяти.\n");
                if (my_text.count == 0)
                    wprintf(L"Error: Не введено ни одного предложения.\n");
                exit(1);
            }
            status = removeRepeated(&my_text);
            if (status < 0) {
                wprintf(L"Error: Ошибка выделения памяти.\n");
                exit(1);
            }
            wprintf(L"Предложения-анаграммы: \n");
            sentenceAnagrams(&my_text);
            freeText(&my_text);
            break;
        case L'2':
            my_text = readText();
            if (my_text.text == NULL) {
                if (my_text.count == -1)
                    wprintf(L"Error: Ошибка выделения памяти.\n");
                if (my_text.count == 0)
                    wprintf(L"Error: Не введено ни одного предложения.\n");
                exit(1);
            }
            status = removeRepeated(&my_text);
            if (status < 0) {
                wprintf(L"Error: Ошибка выделения памяти.\n");
                exit(1);
            }
            wprintf(L"Отсортированный текст по количеству заглавных букв: \n");
            sortSentencesByUpper(&my_text);
            printText(&my_text);
            freeText(&my_text);
            break;
        case L'3':
            my_text = readText();
            if (my_text.text == NULL) {
                if (my_text.count == -1)
                    wprintf(L"Error: Ошибка выделения памяти.\n");
                if (my_text.count == 0)
                    wprintf(L"Error: Не введено ни одного предложения.\n");
                exit(1);
            }
            status = removeRepeated(&my_text);
            if (status < 0) {
                wprintf(L"Error: Ошибка выделения памяти.\n");
                exit(1);
            }
            int result = replaceVowels(&my_text);
            if (result == 0) {
                wprintf(L"Error: Ошибка выделения памяти");
            } else if (result == 1) {
                wprintf(L"Гласные буквы были заменены: \n");
                printText(&my_text);
                freeText(&my_text);
            }
            break;
        case L'4':
            flag;
            word1 = readWord(&flag);
            if (flag == -1) {
                wprintf(L"\nError: Ошибка выделения памяти.\n");
                exit(1);
            }
            word2 = readWord(&flag);
            if (flag == -1) {
                wprintf(L"\nError: Ошибка выделения памяти.\n");
                exit(1);
            }
            my_text = readText();
            if (my_text.text == NULL) {
                if (my_text.count == -1)
                    wprintf(L"Error: Ошибка выделения памяти.\n");
                if (my_text.count == 0)
                    wprintf(L"Error: Не введено ни одного предложения.\n");
                exit(1);
            }
            status = removeRepeated(&my_text);
            if (status < 0) {
                wprintf(L"Error: Ошибка выделения памяти.\n");
                exit(1);
            }           
            res = replaceWordInText(&my_text, word1, word2);
            if (res == 1)  
                wprintf(L"\nСлово `%ls` было заменено на `%ls` во всём тексте:\n", word1, word2);
            if (res == 0)  
                wprintf(L"\nСлово `%ls` не было найдено в тексте. Текст остался прежним: \n", word1);    
            if (res < 0) {
                wprintf(L"Error: Ошибка выделения памяти.\n");
                exit(1);
            }
            free(word1);
            free(word2);
            printText(&my_text);
            freeText(&my_text);
            break;
        case L'5':
            wprintf(L"\n0. Первично обработать текст (удалить дубликаты).\n1. Вывести предложения-анаграммы.\n2. Отсортировать предложения по количеству заглавных букв.\n3. Заменить каждую гласную букву двумя другими буквами следующими по алфавиту.\n4. Заменить все вхождения одного слова на другое.\n5. Вывести справку о функциях\n");
            break;         
        
        case L'9':
            my_text = readText();
            if (my_text.text == NULL) {
                if (my_text.count == -1)
                    wprintf(L"Error: Ошибка выделения памяти.\n");
                if (my_text.count == 0)
                    wprintf(L"Error: Не введено ни одного предложения.\n");
                exit(1);
            }
            status = removeRepeated(&my_text);
            if (status < 0) {
                wprintf(L"Error: Ошибка выделения памяти.\n");
                exit(1);
            }
            palindromInText(&my_text);
            freeText(&my_text);
            break;
        default:
            wprintf(L"Error: Неправильный ввод (введите цифру от 0 до 5)\n");
        }     
    return 0;
}
