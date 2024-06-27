#include "user_functions.h"

int cnt_num_of_secs (struct Text text) {
    int sum = 0;
    for (int i = 0; i < text.amount_of_sentences; i++) {
        struct Sentence *curr_sent = text.sentences[i];
        for (int j = 1; j < curr_sent->amount_of_words; j++) {
            wchar_t *curr_word = word_to_str(curr_sent->words[j]);
            if (wcscmp(curr_word, L"sec") == 0) {
                wchar_t *curr_numb = word_to_str(curr_sent->words[j - 1]);
                if (is_digit(curr_numb)) {
                    sum += wcstol(curr_numb, NULL, 10);
                }
                free(curr_numb);
            }
            free(curr_word);
        }
    }
    return sum;
}


void sort_by_codes_of_1st_words (struct Text *text) {
    qsort(text->sentences, text->amount_of_sentences, sizeof(struct Sentence *), compare_sents);
}


void replace_option_chars (struct Text *text) {
    for (int i = 0; i < text->amount_of_sentences; i++) {
        wchar_t *curr_sent = text->sentences[i]->sentence;
        int mem = (int)wcslen(curr_sent);
        int c = 0;
        for (int j = 0; curr_sent[j]; j++) {
            if (curr_sent[j] == L'%' || curr_sent[j] == L'#') {
                mem += 9;
                c += 1;
            }
            if (curr_sent[j] == L'@') {
                mem += 4;
                c += 1;
            }
        }
        wchar_t *old_curr_sent = realloc(curr_sent, mem * sizeof(wchar_t));
        if (old_curr_sent == NULL) {
            fwprintf(stderr, L"Ошибка перераспределения памяти.\n");
            exit(4);
        } else {
            text->sentences[i]->sentence = old_curr_sent;
        }
        curr_sent = text->sentences[i]->sentence;
        wchar_t percent[] = L"<percent>";
        wchar_t sharp[] = L"<решетка>";
        wchar_t at[] = L"(at)";
        while (c > 0) {
            wchar_t *pnt;
            if ((pnt = wcschr(curr_sent, L'%')) != NULL) {
                insert_word(curr_sent, (int) (pnt - curr_sent), percent);
                c -= 1;
            }
            if ((pnt = wcschr(curr_sent, L'#')) != NULL) {
                insert_word(curr_sent, (int) (pnt - curr_sent), sharp);
                c -= 1;
            }
            if ((pnt = wcschr(curr_sent, L'@')) != NULL) {
                insert_word(curr_sent, (int) (pnt - curr_sent), at);
                c -= 1;
            }
        }
    }
}


void delete_sentences_with_3_consonants (struct Text *text) {
    int i = 0;
    while (i < text->amount_of_sentences) {
        if (word_have_3_consonants(word_to_str(text->sentences[i]->words[text->sentences[i]->amount_of_words - 1]))) {
            delete_sentence(text, i);
        } else {
            i += 1;
        }
    }
}