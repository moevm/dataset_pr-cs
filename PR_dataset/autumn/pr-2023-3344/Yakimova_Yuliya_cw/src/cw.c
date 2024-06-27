#include "structures.h"
#include "input.h"
#include "functions.h"

int main()
{
    setlocale(LC_ALL, "");
    wprintf(L"Course work for option 5.10, created by Yuliya Yakimova.\n");
    
    struct Text *text = malloc(sizeof(struct Text));
    
    wchar_t command = (wchar_t)getwchar();
    getwchar();
    
    switch (command) {
        case L'0': {
            read_text(text);
            print_text(text);
            break;
        }
        
        case L'1': {
            read_text(text);
            find_palindroms(text);
            break;
        }
        
        case L'2': {
            read_text(text);
            replace_spec_symbols(text);
            break;
        }
        
        case L'3': {
            read_text(text);
            sort_sents(text);
            break;
        }
        
        case L'4': {
            read_text(text);
            delete_sents(text);
            print_text(text);
            break;
        }
        
        case L'5': {
            wprintf(L"СПРАВКА\n");
            wprintf(L"\t0 - Вывести текст после первичной обязательной обработки (удалить повторно встречающиеся предложения).\n");
            wprintf(L"\t1 - Для каждого предложения вывести “Палиндромы на месте!” если все слова являются палиндромами, “Кто-то потерял все палиндромы.” если ни одного слово не является палиндромом, в остальных случаях “Чего-то не хватает.”\n");
            wprintf(L"\t2 - Заменить все специальные символы (№*$#@ и дополнительно включая .,;) в тексте на подстроку “>special symbol<”.\n");
            wprintf(L"\t3 - Отсортировать предложения по уменьшению количества латинских букв.\n");
            wprintf(L"\t4 - Удалить все предложения в которых в одном слове встречаются латинские и кириллические буквы.\n");
            wprintf(L"\t5 - Справка.\n");
            break;
        }

        case L'9': {
            wchar_t s[25];
            fgetws(s, 25, stdin);
            for (int i = 0; i < wcslen(s); i++) {
                s[i] =  towlower(s[i]);
            }
            read_text(text);
            print_words(text, s);
            break;
        }
        
        default: {
            wprintf(L"Введена некорректная команда. Завершение работы.\n");
            break;
        }
    }

    return 0;
}
