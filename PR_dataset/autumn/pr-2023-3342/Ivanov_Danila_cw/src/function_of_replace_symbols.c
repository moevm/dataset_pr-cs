#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include "structs.h"

struct Sentence func_of_replace_symbols(struct Sentence input) {
    struct Sentence output;
    output.sentence = calloc(wcslen(input.sentence) * 9 + 1, sizeof(wchar_t));
    int length = input.len_of_sentence;
    int new_length = 0;

    for (int i = 0; i < length; i++) {
        switch (input.sentence[i]) {
            case '%':
                new_length += 9;
                wcscat(output.sentence, L"<percent>");
                break;
            case '#':
                new_length += 9;
                wcscat(output.sentence, L"<решетка>");
                break;
            case '@':
                new_length += 4;
                wcscat(output.sentence, L"(at)");
                break;
            default:
                new_length += 1;
                wcsncat(output.sentence, &input.sentence[i], 1);
                break;
        }
    }
    output.sentence[new_length] = '\0';
    output.len_of_sentence = new_length;
    return output;
}