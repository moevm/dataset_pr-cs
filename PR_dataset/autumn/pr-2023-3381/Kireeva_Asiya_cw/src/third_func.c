#include "third_func.h"

void third_func() {
    struct Text text = get_text();
    for (int i = 0; i < text.number_of_sentences; i++) {
        for (int j = 0; j < text.text[i]->number_of_letters; j++) {
            wchar_t *word;
            if (text.text[i]->sentence[j] == L'%') {
                word = L"<percent>";
            } else if (text.text[i]->sentence[j] == L'#') {
                word = L"<решетка>";
            } else if (text.text[i]->sentence[j] == L'@') {
                word = L"(at)";
            } else {
                continue;
            }
            text.text[i]->number_of_letters += wcslen(word) - 1;
            text.text[i]->sentence = (wchar_t *) realloc(text.text[i]->sentence,
                                                         (text.text[i]->number_of_letters + 1) * sizeof(wchar_t));
            wmemmove(text.text[i]->sentence + j + wcslen(word), text.text[i]->sentence + j + 1,
                     text.text[i]->number_of_letters - j - wcslen(word) + 1);
            wmemmove(text.text[i]->sentence + j, word, wcslen(word));
        }
    }
    for (int i = 0; i < text.number_of_sentences; i++) {
        wprintf(L"%ls\n", text.text[i]->sentence);
    }
    free_space(text);
}