#include <memory.h>
#include <stdlib.h>
#include <wchar.h>
#include "sentence.h"
#include "token.h"

#define EXTENSION_TOKEN_COUNT 20
#define COLOR_DEFAULT L"\x1b[0m"


struct Sentence {
    Token **tokens;
    size_t tokens_count;
    size_t tokens_allocated_size;
};

Sentence *Sentence_create() {
    Sentence *new = (Sentence *) malloc(sizeof(Sentence));
    if (!new) {
        return NULL;
    }

    new->tokens = (Token **) malloc(0);
    if (!new->tokens) {
        free(new);
        return NULL;
    }

    new->tokens_count = 0;
    new->tokens_allocated_size = 0;

    return new;
}

void Sentence_destroy(Sentence *sentence) {
    for (size_t i = 0; i < sentence->tokens_count; i++) {
        Token_destroy((sentence->tokens[i]));
    }
    free(sentence->tokens);
    free(sentence);
    sentence = NULL;
}

size_t Sentence_get_tokens_count(Sentence *sentence) {
    return sentence->tokens_count;
}

Token *Sentence_get_token(Sentence *sentence, size_t index) {
    return sentence->tokens[index];
}

void Sentence_set_token(Sentence *sentence, Token *new_token, size_t index) {
    if (sentence->tokens[index]) {
        Token_destroy(sentence->tokens[index]);
    }
    sentence->tokens[index] = new_token;
}

Sentence *Sentence_extend(Sentence *sentence, size_t extension_token_count) {
    size_t new_size = sentence->tokens_allocated_size + (extension_token_count * sizeof(Token *));
    Token **temp = (Token **) realloc(sentence->tokens, new_size);
    if (!temp) {
        return NULL;
    }
    sentence->tokens = temp;
    sentence->tokens_allocated_size = new_size;

    return sentence;
}

Sentence *Sentence_append_token(Sentence *sentence, Token *token) {
    while ((sentence->tokens_count + 1) * sizeof(Token *) > sentence->tokens_allocated_size) {
        if (!Sentence_extend(sentence, EXTENSION_TOKEN_COUNT)) {
            return NULL;
        }
    }

    sentence->tokens[sentence->tokens_count] = token;
    sentence->tokens_count++;

    return sentence;
}

Sentence *Sentence_optimize_size(Sentence *sentence) {
    size_t real_tokens_size = sentence->tokens_count * sizeof(Token *);
    if (real_tokens_size == sentence->tokens_allocated_size) {
        return sentence;
    }
    Token **tokens_temp = (Token **) realloc(sentence->tokens, real_tokens_size);
    if (!tokens_temp) {
        return NULL;
    }
    sentence->tokens = tokens_temp;
    sentence->tokens_allocated_size = real_tokens_size;

    return sentence;
}

size_t Sentence_count_word_occurrences(Sentence *sentence, wchar_t *word) {
    size_t cnt = 0;
    for (size_t i = 0; i < sentence->tokens_count; i += 2) {
        if (wcscasecmp(Token_get_text(sentence->tokens[i]), word) == 0) {
            cnt++;
        }
    }

    return cnt;
}

Sentence *Sentence_color_word(Sentence *sentence, wchar_t *word, wchar_t *color_text) {
    for (size_t i = 0; i < sentence->tokens_count; i += 2) {
        wchar_t *token_text = Token_get_text(sentence->tokens[i]);
        if (wcscasecmp(token_text, word) == 0) {
            size_t replace_str_len = wcslen(color_text) + wcslen(token_text) + wcslen(COLOR_DEFAULT);
            wchar_t *replace_str = (wchar_t *) malloc((replace_str_len + 1) * sizeof(wchar_t));
            if (!replace_str) {
                free(replace_str);
                return NULL;
            }
            wcscpy(replace_str, color_text);
            wcscat(replace_str, token_text);
            wcscat(replace_str, COLOR_DEFAULT);

            Token *new_word = Token_create(replace_str);
            if (!new_word) {
                return NULL;
            }

            Token_destroy(sentence->tokens[i]);
            sentence->tokens[i] = new_word;
        }
    }

    return sentence;
}

int Sentence_word_count_compare(const void *a, const void *b) {
    size_t a_cnt = (*(Sentence **) a)->tokens_count / 2;
    size_t b_cnt = (*(Sentence **) b)->tokens_count / 2;
    return (int) (a_cnt - b_cnt);
}
