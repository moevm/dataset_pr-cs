#include "../include/main.h"

#define LOCALE ""

int main() {
    setlocale(LC_ALL, LOCALE);
    wprintf(L"Course work for option 5.9, created by Mikhail Atoyan.\n");
    int command = get_command();
    switch (command) {
        case 0:
            print_text(get_text());
            break;
        case 1:
            print_text(replace_text(get_text()));
            break;
        case 2: 
            print_colorized(get_text());
            break;
        case 3:
            print_text(sort_sentences(get_text())); 
            break;
        case 4:
            print_text(filter(get_text()));
            break;
        case 9:
            wchar_t *word = get_word();
            print_words_from_text(word, get_text());
            break;
        case 5: 
            wprintf(L"0 – вывод текста после первичной обязательной обработки (если предусмотрена заданием данного уровня сложности).\n"
                    "1 - Изменить все слова в тексте заканчивающиеся на “ться” так чтобы они заканчивались на “тся” и наоборот.\n"
                    "2 – Вывести все предложения в которых встречается второе слово первого предложения. Данное слово необходимо выделить зеленым цветом.\n"
                    "3 – Отсортировать предложения по возрастанию количества слов в предложении.\n"
                    "4 – Удалить все предложения в которых больше 10 слов.\n"
                    "5 – вывод справки о функциях, которые реализует программа.\n");
            break;
        default:
            fwprintf(stderr, L"Error: Incorrect command. Input 5 for list of possible commands.\n");
    }
    return 0;
} 