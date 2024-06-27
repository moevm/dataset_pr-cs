#include <stdbool.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include "token.h"
#include "utils.h"


struct Token {
    wchar_t *text;
    size_t length;
};

Token *Token_create(wchar_t *text) {
    Token *new = (Token *) malloc(sizeof(Token));
    if (!new) {
        return NULL;
    }

    size_t length = wcslen(text);
    new->text = wcsdup(text);
    if (!new->text) {
        free(new);
        return NULL;
    }

    new->length = length;

    return new;
}

void Token_destroy(Token *token) {
    if (!token) return;
    free(token->text);
    free(token);
    token = NULL;
}

size_t Token_get_length(Token *token) {
    return token->length;
}

wchar_t *Token_get_text(Token *token) {
    return token->text;
}

bool Token_is_consists_of_chars(Token *token, wchar_t *chars) {
    wchar_t *chars_lower = wcs_to_lower(chars);
    wchar_t *token_text_lower = wcs_to_lower(token->text);

    for (size_t i = 0; i < token->length; i++) {
        bool is_consists = false;
        for (size_t j = 0; j < wcslen(chars); j++) {
            if (token_text_lower[i] == chars_lower[j]) {
                is_consists = true;
                break;
            }
        }
        if (!is_consists) {
            free(chars_lower);
            free(token_text_lower);
            return false;
        }
    }
    free(chars_lower);
    free(token_text_lower);

    return true;
}
