#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <locale.h>

#include "structs.h"
#include "input.h"
#include "output.h"
#include "free_memory.h"
#include "checking_symbol.h"

void delete_cyrillic_latin() {
    Text* text = (Text*)malloc(sizeof(Text));
    text->sentences = (Sentence*)malloc(sizeof(Sentence));
    input_text(text);
    for (int i = 0; i < text->size_text; i++) {
        const wchar_t separators[] = L" ,.";
        wchar_t* ptr;
        wchar_t* copy = wcsdup (text->sentences[i].str);
        wchar_t* token = wcstok(copy, separators, &ptr);
        int check_delete = 0;
        while (token != NULL) {
            int count_latin = 0;
            int count_cyrillic = 0;
            for (int i = 0; i < wcslen(token); i++) {
                if (is_latin(token[i])) {
                    count_latin++;
                }
                if (is_cyrillic(token[i])) {
                    count_cyrillic++;
                }
            }
            if (count_latin > 0 && count_cyrillic > 0) {
                text->sentences[i].str[0] = '\0';
            }
            token = wcstok(NULL, separators, &ptr);
        }
    }
    for (int i = 0; i < text->size_text; i++) {
        if (text->sentences[i].str[0] == '\0') {
            int check = 1;
            for (int j = i + 1; j < text->size_text; j++) {
                if (text->sentences[j].str[0] != '\0') {
                    Sentence buf = text->sentences[i];
                    text->sentences[i] = text->sentences[j];
                    text->sentences[j] = buf;
                    j = text->size_text;
                    check = 0;
                }
            }
            if (check) {
                text->size_text = i;
                text->sentences = (Sentence*)realloc(text->sentences, text->size_text * sizeof(Sentence));
            }
        }
    }
    output_text(text);
    free_text(text);
}

