#include "PaintWords.h"

void PaintWords(struct Text* txt) {
    for (int i = 0; i < txt->l; i++) {
        struct Sentence* sentence = txt->txt[i];

        if (sentence == NULL || sentence->str == NULL) {
            continue;
        }

        wchar_t* str = sentence->str;
        wchar_t* word_start = NULL;

        for (int j = 0; j <= wcslen(str); j++) {
            if (str[j]!= L',' && str[j]!= L'.' && !iswspace(str[j])) {
                if (word_start == NULL) {
                    word_start = &str[j];
                }
            } else {
                if (word_start != NULL) {
                    wchar_t* word = (wchar_t*)malloc(((&str[j] - word_start) + 1) * sizeof(wchar_t));
                    wcsncpy(word, word_start, (&str[j] - word_start));
                    word[(&str[j] - word_start)] = L'\0';
                    
                    int color = wcslen(word) % 4;

                    switch (color) {
                        case 0:
                            wprintf(L"\033[31m%ls\033[0m", word); // Red
                            break;
                        case 1:
                            wprintf(L"\033[34m%ls\033[0m", word); // Blue
                            break;
                        case 2:
                            wprintf(L"\033[32m%ls\033[0m", word); // Green
                            break;
                        case 3:
                            wprintf(L"\033[33m%ls\033[0m", word); // Yellow
                            break;
                        default:
                            wprintf(L"%ls", word); // Default color
                            break;
                    }

                    free(word);
                    word_start = NULL;
                }

                wprintf(L"%lc", str[j]);
            }
        }

        wprintf(L"\n");
    }
}
