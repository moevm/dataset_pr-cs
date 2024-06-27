#ifndef CW_TOKEN_H
#define CW_TOKEN_H

#include <stdbool.h>
#include <wchar.h>

struct Token;
typedef struct Token Token;

Token *Token_create(wchar_t *text);

void Token_destroy(Token *token);

size_t Token_get_length(Token *token);

wchar_t *Token_get_text(Token *token);

bool Token_is_consists_of_chars(Token *token, wchar_t* chars);

#endif //CW_TOKEN_H
