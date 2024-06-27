#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <locale.h>

#include "input.h"
#include "structs.h"
#include "free_memory.h"

void palindrome() {
    Text* text = (Text*)malloc(1 * sizeof(Text));
    text->sentences = (Sentence*)malloc(sizeof(Sentence));
    input_text(text);
    for (int i = 0; i < text->size_text; i++) {
        const wchar_t separators[] = L" ,.";
        wchar_t* ptr;
        wchar_t* token = wcstok(text->sentences[i].str, separators, &ptr);
        int count_token = 0;
        int count_palindrome = 0;
        while (token != NULL) {
            int iteration = 0;
            int same_symbol = 0;
            for (int j = 0; j < wcslen(token) / 2; j++) {
                if (token[j] == token[wcslen(token) - j - 1]) {
                    same_symbol++;
                }
                iteration++;
            }
            if (same_symbol == iteration) {
                count_palindrome++;
            }
            count_token++;
            token = wcstok(NULL, separators, &ptr);
        }
        if (count_palindrome == count_token) {
            wprintf(L"Палиндромы на месте!\n");
        }
        if (count_palindrome == 0) {
            wprintf(L"Кто-то потерял все палиндромы.\n");
        }
        if (count_palindrome < count_token && count_palindrome != 0) {
            wprintf(L"Чего-то не хватает.\n");
        }
    }
    free_text(text);
}

