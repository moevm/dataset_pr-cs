#include <stdlib.h>
#include <wchar.h>

#include "structures.h"
#include "printFunctions.h"

void replaceSpecialSymbols(struct Text *textStructured) {

    // Принимает на вход структуру Text. Заменяет все специальные символы delims на подстроку >special symbol< и перезаписывает массивы символов в структуре, которую принимат 

    wchar_t *delims = L".,;!@#$^&*()";
    wchar_t *new_sentence;
    wchar_t *toAdd = L">special symbol<";
    
    for (int i = 0; i < textStructured->len; i++) {

        new_sentence = malloc(sizeof(wchar_t) * (wcslen(textStructured->sentences[i]->sentence) + 10));
        if (new_sentence == NULL) {
            printError(L"ERROR: unable to allocate memory in replaceSpecialSymbols");
        }
        new_sentence[0] = L'\0';

        for (int j = 0; j < wcslen(textStructured->sentences[i]->sentence); j++) {

            if (wcschr(delims, textStructured->sentences[i]->sentence[j])) {
                new_sentence = realloc(new_sentence, sizeof(wchar_t) * (wcslen(new_sentence) + wcslen(toAdd) + 10));
                if (new_sentence == NULL) {
                    printError(L"ERROR: unable to reallocate memory in replaceSpecialSymbols");
                }
                wcscat(new_sentence, toAdd);
            } else {
                int len = wcslen(new_sentence);
                new_sentence = realloc(new_sentence, sizeof(wchar_t) * (len + 2));
                new_sentence[len] = textStructured->sentences[i]->sentence[j];
                new_sentence[len + 1] = L'\0';
            
            }

        }

        free(textStructured->sentences[i]->sentence); 
        textStructured->sentences[i]->sentence = new_sentence;
        
    }

}