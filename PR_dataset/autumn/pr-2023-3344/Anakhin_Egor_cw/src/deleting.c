#include <ctype.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <ctype.h>

#include "structures.h"

int differentLanguages(const wchar_t* sentence) {

    // Принимает на вход предложение. Возвращает 1, если есть и кириллица и латиница в предложении, иначе 0

    int has_latin = 0;
    int has_cyrillic = 0;

    for (int i = 0; sentence[i] != L'\0'; i++) {
        if (iswalpha(sentence[i])) {
            if (sentence[i] >= L'a' && sentence[i] <= L'z' ||
                sentence[i] >= L'A' && sentence[i] <= L'Z') {
                has_latin = 1;
            } else if (sentence[i] >= L'а' && sentence[i] <= L'я' ||
                       sentence[i] >= L'А' && sentence[i] <= L'Я') {
                has_cyrillic = 1;
            }
        }

        if (has_latin && has_cyrillic) {
            return 1;
        }
    }

    return 0;

}

void deletingSentenceFromText(struct Text *textStructured, int index) {

    // Принимает на вход структуру Text и индекс предложения, которое нужно удалить. Далее удаляет это предложение, смещая все предложения после на 1 позицию назад

    free(textStructured->sentences[index]);

    for (int i = index; i < textStructured->len-1; i++) {
        textStructured->sentences[i] = textStructured->sentences[i+1];
    }

    textStructured->len--;

}


void deleteDifferentLanguages(struct Text *textStructured) {

    // Принимает на вход структуру Text и удаляет все предложения, в которых есть и латинские и кириллические символы

    for (int i = 0; i < textStructured->len;) {
        if (differentLanguages(textStructured->sentences[i]->sentence)) {
            deletingSentenceFromText(textStructured, i);
        } else {
            i++;
        }
    }

    if (textStructured->len == 0) {
        wprintf(L"\033[1;33mAll sentences contained cyrillic and latin letters so TEXT is empty\033\n");
    }

}