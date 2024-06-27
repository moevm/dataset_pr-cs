#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

#include "structures.h"

int palindrom(wchar_t *word) {

    // Принимает на вход слово. Сравнивает символы слева с символами справа. Возвращает 0, если не палиндром, в противном случае 1
    wchar_t *new_word = wcstok(word, L",", &word);
    for (int i = 0; i < wcslen(new_word) / 2; i++) {
        if (towlower(new_word[i]) != towlower(new_word[wcslen(new_word) - i - 1])) {
            return 0;
        }
    }
    return 1;
    
}

void palindromsInText(struct Text *textStructured) {

    // Принимает на вход структуру Text. Проверяет все слова в каждом предложении и выводит для каждого свое пояснение, в зависимости от количества палиндромов

    int count;
    int palindromCount;
    wchar_t *word;
    wchar_t *sentenceCopy;

    for (int i = 0; i < textStructured->len; i++) {
        sentenceCopy = malloc((wcslen(textStructured->sentences[i]->sentence) + 30) * sizeof(wchar_t));
        count = 0;
        palindromCount = 0;
        wcscpy(sentenceCopy, textStructured->sentences[i]->sentence);
        word = wcstok(sentenceCopy, L" ", &sentenceCopy);
        while (word != NULL) {
            count++;
            palindromCount += palindrom(word);
            word = wcstok(NULL, L" ", &sentenceCopy);
        }
        free(sentenceCopy);
        if (palindromCount == 0) {
            wprintf(L"(%ls) - Кто-то потерял все палиндромы.\n", textStructured->sentences[i]->sentence);
        } else if (palindromCount == count) {
            wprintf(L"(%ls) - Палиндромы на месте!\n", textStructured->sentences[i]->sentence);
        } else {
            wprintf(L"(%ls) - Чего-то не хватает.\n", textStructured->sentences[i]->sentence);
        }
    }

}