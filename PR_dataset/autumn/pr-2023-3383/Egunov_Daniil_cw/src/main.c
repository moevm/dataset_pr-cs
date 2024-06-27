#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <getopt.h>
#include "input.h"
#include "output.h"
#include "text.h"
#include "text_processing.h"
#include "utils.h"


int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "");

    bool remove_duplicate_whitespaces = false;
    bool correct_spaces_with_commas = false;

    int arg;
    opterr = 0;
    while ((arg = getopt(argc, argv, "cdh")) != -1) {
        switch (arg) {
            case 'c':
                correct_spaces_with_commas = true;
                break;
            case 'd':
                remove_duplicate_whitespaces = true;
                break;
            case 'h':
                print_help();
                return 0;
            default:
                print_err_invalid_option();
                return 0;
        }
    }

    wprintf(L"Course work for option 5.9, created by Daniil Egunov.\n");

    int option;
    if (wscanf(L"%d", &option) != 1) {
        print_err_no_option();
        return 0;
    }

    Text *text;
    if ((option >= 0 && option <= 4) || option == 9) {
        text = read_text(remove_duplicate_whitespaces, correct_spaces_with_commas);
        if (!text) {
            print_err_no_mem();
            return 0;
        }
        if (Text_get_length(text) == 0) {
            print_err_text_empty();
            Text_destroy(text);
            return 0;
        }
    }

    switch (option) {
        case 0: {
            print_text(text);
            break;
        }
        case 1: {
            if (!edit_verbs(text)) {
                print_err_no_mem();
                Text_destroy(text);
                return 0;
            }
            print_text(text);
            break;
        }
        case 2: {
            Sentence *sentence = Text_get_sentence(text, 0);
            if (Sentence_get_tokens_count(sentence) / 2 < 2) {
                print_err_not_enough_words_in_sentence(0);
                Text_destroy(text);
                return 0;
            }
            wchar_t *word_to_find = wcsdup(Token_get_text(Sentence_get_token(sentence, 2)));
            if (!word_to_find || !find_word(text, word_to_find)) {
                print_err_no_mem();
                Text_destroy(text);
                return 0;
            }
            free(word_to_find);
            print_text(text);
            break;
        }
        case 3: {
            qsort(Text_get_sentences(text), Text_get_length(text), sizeof(Sentence *), Sentence_word_count_compare);
            print_text(text);
            break;
        }
        case 4: {
            if (!delete_long_sentences(text, 10)) {
                print_err_no_mem();
                Text_destroy(text);
                return 0;
            }
            print_text(text);
            break;
        }
        case 5: {
            print_help();
            return 0;
        }
        case 9: {
            Sentence *sentence = Text_get_sentence(text, 0);
            wchar_t *word = wcsdup(Token_get_text(Sentence_get_token(sentence, 0)));
            if (!word) {
                print_err_no_mem();
                Text_destroy(text);
                return 0;
            }

            Sentence *out_sentence = find_words_consisting_of_chars(text, word);
            free(word);
            if (!out_sentence) {
                print_err_no_mem();
                Text_destroy(text);
                return 0;
            }
            print_sentence_by_tokens(out_sentence);
            Sentence_destroy(out_sentence);
            break;
        }
        default: {
            print_err_invalid_option();
            return 0;
        }
    }

    Text_destroy(text);

    return 0;
}
