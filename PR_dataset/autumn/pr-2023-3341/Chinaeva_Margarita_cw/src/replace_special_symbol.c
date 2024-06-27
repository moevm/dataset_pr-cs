#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <locale.h>

#include "structs.h"
#include "input.h"
#include "output.h"
#include "free_memory.h"
#include "checking_symbol.h"

void replace_special_symbol() {
    Text* text = (Text*)malloc(sizeof(Text));
    text->sentences = (Sentence*)malloc(sizeof(Sentence));
    input_text(text);
    Text* text_with_replace_symbols = (Text*)malloc(sizeof(Text));
    text_with_replace_symbols->size_text = text->size_text;
    text_with_replace_symbols->sentences = (Sentence*)calloc(text_with_replace_symbols->size_text, sizeof(Sentence));

    for (int i = 0; i < text->size_text; i++) {
        int count_special_symbol = 0;
        for (int j = 0; j < text->sentences[i].size_str; j++) {
            if (is_special_symbol(text->sentences[i].str[j])) {
                count_special_symbol++;
            }
        }
        wchar_t* str_sp_sy = L">special symbol<";
        text_with_replace_symbols->sentences[i].str = (wchar_t*)calloc((text->sentences[i].size_str + count_special_symbol * wcslen(str_sp_sy) + 1), sizeof(wchar_t));

        int q = 0;
        for (int j = 0; j < text->sentences[i].size_str; j++) {
            if (is_special_symbol(text->sentences[i].str[j])) {
                for (int k = 0; k < wcslen(str_sp_sy); k++) {
                    text_with_replace_symbols->sentences[i].str[q] = str_sp_sy[k];
                    q++;
                }
            } else {
                text_with_replace_symbols->sentences[i].str[q] = text->sentences[i].str[j];
                q++;
            }
        }

        text_with_replace_symbols->sentences[i].size_str = wcslen(text_with_replace_symbols->sentences[i].str);
    }
    output_text(text_with_replace_symbols);
    free_text(text);
    free_text(text_with_replace_symbols);
}
