#include "regex_task.h"

#include <locale.h>
#include <stdlib.h>
#include <wchar.h>

#include "util/config.h"
#include "util/error.h"

int check_word(wchar_t* word, wchar_t* expression);

void regex_task(Text* _text, wchar_t* expression) {
    const wchar_t* seps = L" ,.";
    wchar_t* context = NULL;
    setlocale(LC_ALL, LOCALE);

    for (unsigned int i = 0; i < _text->len; i++) {
        char all_match = 1;
        wchar_t* str_dup = wcsdup(_text->body[i]->body);
        wchar_t* word = wcstok(str_dup, seps, &context);
        while (word != NULL) {
            if (!check_word(word, expression)) {
                all_match = 0;
                break;
            }
            word = wcstok(NULL, seps, &context);
        }
        free(str_dup);
        if (!all_match)
            clear(&_text->body[i]);
    }
}

int check_word(wchar_t* word, wchar_t* expression) {
    int carriage_pos = 0;
    int match = 0;
    if (expression[carriage_pos] == L'*' && expression[carriage_pos + 1] == L'\0' && word[carriage_pos] != L'\0' ||
        (expression[carriage_pos] == L'\0' && word[carriage_pos] == L'\0')) {
        return 1;
    }

    while (expression[carriage_pos] != L'\0' && word[carriage_pos] != L'\0') {
        if (expression[carriage_pos] == L'*') {
            if (word[carriage_pos + 1] == L'\0')
                return 1;

            for (unsigned int i = 0; word[i] != L'\0'; i++) {
                if (check_word(&word[carriage_pos + i], &expression[carriage_pos + 1]))
                    return 1;
            }
            return 0;
        } else if (expression[carriage_pos] == L'?' || expression[carriage_pos] == word[carriage_pos]) {
            carriage_pos++;
        } else {
            return 0;
            break;
        }
        match = 1;
    }
    if (expression[carriage_pos] == L'\0' && word[carriage_pos] != L'\0')
        return 0;

    return match;
}
