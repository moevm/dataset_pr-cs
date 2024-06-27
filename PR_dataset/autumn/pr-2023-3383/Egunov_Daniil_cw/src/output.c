#include <stdio.h>
#include <wchar.h>
#include "output.h"
#include "text.h"
#include "token.h"
#include "sentence.h"


void print_sentence(Sentence *sentence) {
    for (size_t i = 0; i < Sentence_get_tokens_count(sentence); i++) {
        wprintf(L"%ls", Token_get_text(Sentence_get_token(sentence, i)));
    }
}

void print_text(Text *text) {
    for (size_t i = 0; i < Text_get_length(text); i++) {
        print_sentence(Text_get_sentence(text, i));
        wprintf(L"\n");
    }
}

void print_sentence_by_tokens(Sentence *sentence) {
    for (size_t i = 0; i < Sentence_get_tokens_count(sentence); i++) {
        wprintf(L"%ls", Token_get_text(Sentence_get_token(sentence, i)));
    }
}

void print_help() {
    wprintf(L"Usage: cw [-h] [-c] [-d]\n\n"
            "\t-c\tcorrect whitespaces with commas\n"
            "\t-d\tdelete duplicating whitespace characters\n"
            "\t-h\thelp message\n\n"
            "\x1b[1;4mРеализованы следующие функции:\x1b[0m\n"
            "1) Программа преобразует все слова, завершающиеся на \"ться\", в форму с окончанием \"тся\", и наоборот. "
            "Поиск осуществляется без учёта регистра, и все замены приводятся к нижнему регистру.\n"
            "2) Программа выделяет зелёным все включения второго слова первого предложения (без учёта регистра). "
            "Предложения, в которых нет этого слова, удаляются.\n"
            "3) Программа сортирует предложения по возрастанию количества слов.\n"
            "4) Программа удаляет все предложения, в которых больше 10 слов.\n"
            "5) Вывод справки.\n");
}

void print_err_no_mem() {
    fwprintf(stderr, L"\x1b[31mERROR: Memory allocation error.\x1b[0m\n");
}

void print_err_no_option() {
    fwprintf(stderr, L"\x1b[31mERROR: No option has been entered.\x1b[0m\n");
}

void print_err_invalid_option() {
    fwprintf(stderr, L"\x1b[31mERROR: Invalid option value has been entered.\x1b[0m\n");
}

void print_err_text_empty() {
    fwprintf(stderr, L"\x1b[31mERROR: The text is empty.\x1b[0m\n");
}

void print_err_not_enough_words_in_sentence(size_t sentence_index) {
    fwprintf(stderr, L"\x1b[31mERROR: There are not enough words in the sentence %zu.\x1b[0m\n", sentence_index + 1);
}
