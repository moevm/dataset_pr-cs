#include <memory.h>
#include <stdlib.h>
#include <wchar.h>
#include "text_processing.h"
#include "text.h"
#include "token.h"
#include "sentence.h"
#include "utils.h"

#define GREEN L"\x1b[32m"

Text *edit_verbs(Text *text) {
    for (size_t i = 0; i < Text_get_length(text); i++) {
        Sentence *sentence = Text_get_sentence(text, i);
        for (size_t j = 0; j < Sentence_get_tokens_count(sentence); j += 2) {
            Token *token = Sentence_get_token(sentence, j);
            size_t token_len = Token_get_length(token);
            if (token_len < 3) continue;
            wchar_t *token_text = Token_get_text(token);

            bool is_base_form_verb = wcscaseends(token_text, L"ться");
            bool is_non_base_form_verb = wcscaseends(token_text, L"тся");
            if (!is_base_form_verb && !is_non_base_form_verb) continue;

            wchar_t *new_token_text = (wchar_t *) malloc((token_len + 2) * sizeof(wchar_t));
            if (!new_token_text) {
                free(new_token_text);
                return NULL;
            }
            wcscpy(new_token_text, token_text);

            if (is_base_form_verb) {
                wcscpy(&new_token_text[token_len - 4], L"тся");
            } else {
                wcscpy(&new_token_text[token_len - 3], L"ться");
            }

            Token *new_token = Token_create(new_token_text);
            free(new_token_text);
            if (!new_token) {
                return NULL;
            }
            Sentence_set_token(sentence, new_token, j);
        }
    }
    return text;
}

Text *find_word(Text *text, wchar_t *word) {
    Sentence *sentence;
    for (size_t i = 0; i < Text_get_length(text); i++) {
        sentence = Text_get_sentence(text, i);
        if (Sentence_count_word_occurrences(sentence, word) > 0) {
            if (!Sentence_color_word(sentence, word, GREEN)) {
                return NULL;
            }
        } else {
            Text_delete_sentence(text, i);
            i--;
        }
    }

    if (!Text_optimize_size(text)) {
        return NULL;
    }

    return text;
}

Text *delete_long_sentences(Text *text, size_t max_words_count) {
    for (size_t i = 0; i < Text_get_length(text); i++) {
        if (Sentence_get_tokens_count(Text_get_sentence(text, i)) / 2 > max_words_count) {
            Text_delete_sentence(text, i);
        }
    }

    if (!Text_optimize_size(text)) {
        return NULL;
    }

    return text;
}

Sentence *find_words_consisting_of_chars(Text *text, wchar_t *chars) {
    Sentence *res_sentence = Sentence_create();

    for (size_t i = 0; i < Text_get_length(text); i++) {
        Sentence *sentence = Text_get_sentence(text, i);
        for (size_t j = 0; j < Sentence_get_tokens_count(sentence); j += 2) {
            if (i == 0 && j == 0) continue;
            Token *token = Sentence_get_token(sentence, j);

            if (Token_is_consists_of_chars(token, chars)) {
                Token *new_word = Token_create(Token_get_text(token));
                Token *new_separator = Token_create(L"\n");
                if (!new_word || !new_separator) {
                    Token_destroy(new_word);
                    Token_destroy(new_separator);
                    Sentence_destroy(res_sentence);
                    return NULL;
                }
                if (!Sentence_append_token(res_sentence, new_word) ||
                    !Sentence_append_token(res_sentence, new_separator)) {
                    Token_destroy(new_word);
                    Token_destroy(new_separator);
                    Sentence_destroy(res_sentence);
                    return NULL;
                }
            }
        }
    }

    return res_sentence;
}
