#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

#include "structures.h"

void back(struct Text* text) {
    for (int i = 0; i < text->len; ++i) {
        wchar_t* pred = text->sentences[i]->sentence; 
        
        // Вычисляем длину строки pred, учитывая символы переноса строки
        int len = 0;
        while (pred[len] != L'\0') {
            len++;
        }
        wchar_t reversed[len+1];
        int j = 0;
        
        for (int k = len - 1; k >= 0; k--) {
            if (pred[k] == L' ' || pred[k] == L',' || pred[k] == L'.') {
                reversed[j++] = pred[k];
            } else {
                int start = k;
                while (k > 0 && pred[k - 1] != L' ' && pred[k - 1] != L',' && pred[k - 1] != L'.') {
                    k--;
                }
                for (int l = k; l <= start; l++) { 
                    reversed[j++] = pred[l];
                }   
            }
        }
        
        for (int l = 0; l < len + 1; l++) {
            if (reversed[l] == L' ' && (reversed[l + 1] == L',' || reversed[l + 1] == L';' || reversed[l + 1] == L':') && reversed[l + 2] != L' ') {
                wchar_t temp = reversed[l];
                reversed[l] = reversed[l + 1];
                reversed[l + 1] = temp;
            }
        }
        
        reversed[j] = '\0';
        
        free(text->sentences[i]->sentence);
        text->sentences[i]->sentence = malloc((j + 1) * sizeof(wchar_t));
        wcscpy(text->sentences[i]->sentence, reversed);
        
        text->sentences[i]->len = j;
    }
}
