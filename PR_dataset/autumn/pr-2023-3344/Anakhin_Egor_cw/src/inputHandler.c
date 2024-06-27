#include <wctype.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>


#include "structures.h"
#include "printFunctions.h"


int start() {

    // Функция для начала предложения. Считывает опции. Возвращает номер опции.

    wprintf(L"Course work for option 5.10, created by Egor Anakhin.\n");
    // wprintf(L"Введите номер опции: ");

    int option;

    wscanf(L"%d", &option);

    getwchar();
    return option;

}

wchar_t* reading() {

    // Функция считывания текста. Считывает все символы до того, как будет два \n подряд. Возвращает весь необработанных текст одним массивом

    setlocale(LC_CTYPE, "");
    wchar_t *text = malloc(10 * sizeof(wchar_t));
    if (text == NULL) {
        printError(L"ERROR: failed to allocate memory for text");
        free(text);
        return L" ";
    }

    wchar_t character = getwchar();
    int break_count = 0;
    int leng = 0;

    while (1) {

        if (character == L'\n') {
            break_count++;
        } else {
            break_count = 0;
        }

        if (break_count == 2) {
            break;
        }

        *(text + leng++) = character;
        text = realloc(text, (10 + wcslen(text)) * sizeof(wchar_t));
        if (text == NULL) {
            free(text);
            printError(L"ERROR: failed to reallocate memory for text");
            return L" ";
        }

        character = getwchar();
    }

    *(text + leng) = L'\0';
    return text;

}

int sentenceExists(struct Text *textStructured, wchar_t *sentence) {

    // функция проверки, сущесвтует ли предложение. Сравнивает входную структуру с каждой структурой в Text. Возвращает 1, если существует такое предложение, 0, если не существует

    for (int i = 0; i < textStructured->len; i++) {
        int j;
        for (j = 0; j < textStructured->sentences[i]->len && j < wcslen(sentence); j++) {
            if (towlower(textStructured->sentences[i]->sentence[j]) != towlower(sentence[j])) {
                break;
            }
        }
        if (j == textStructured->sentences[i]->len && j == wcslen(sentence)) {
            return 1;
        }
    }
    return 0;

}

void deleteWhiteSpaces(struct Text *sentencesArray) {

    // Принимает на вход структуру Text. Удаляет все незначащие пробелы из начала предложения

    for (int j = 0; j < sentencesArray->len; j++) {
        while (sentencesArray->sentences[j]->sentence[0] == L' ' || sentencesArray->sentences[j]->sentence[0] == L'\n') {
            for(int i = 0; i < sentencesArray->sentences[j]->len; i++) {
                sentencesArray->sentences[j]->sentence[i] = sentencesArray->sentences[j]->sentence[i+1];
            }
        }
    }

}

void addSentencesToText(struct Text *textStructured, wchar_t *text) {

    // Функция разбиения текста по структурам. На вход подается структура Text и необработанный текст

    wchar_t* token = wcstok(text, L".", &text);

    while (token != NULL) {
        if (token != L"\n") {
            struct Sentence *newSentence = malloc(sizeof(struct Sentence));
            newSentence->sentence = malloc((wcslen(token) + 20) * sizeof(wchar_t));
            if (newSentence->sentence == NULL) {
                printError(L"\nERROR: failed to allocate memory for struct Sentence *newSentence\n");
                exit(1);
            }
            wcscpy(newSentence->sentence, token);
            newSentence->len = wcslen(token);
            textStructured->sentences = realloc(textStructured->sentences, (textStructured->len + 30) * sizeof(struct Sentence*));
            if (textStructured->sentences == NULL) {
                printError(L"ERROR: failed to reallocate memory for textStructed->sentences");
                exit(1);
            }
            if (!sentenceExists(textStructured, newSentence->sentence)) {
                textStructured->sentences[textStructured->len] = newSentence;
                textStructured->len++;
            }
        }
        token = wcstok(NULL, L".", &text);
    }

    free(text);

    deleteWhiteSpaces(textStructured);
    
}

int wrapper(void (*function)(struct Text *), struct Text *sentencesArray) {

    // функция оберта. Принимает на вход функцию, которую нужно сделать и структуру, с которой нужно произвести операцию. Возвращает 0, если все прошло успешно, иначе возвращает 1, если считанный текст был равен \n\n

    setlocale(LC_CTYPE, "");

    wchar_t *new_text = reading();

    if (wcscmp(new_text, L"\0") == 0) {
        printError(L"error at wrapper");
        return 1;
    }

    addSentencesToText(sentencesArray, new_text);
    deleteWhiteSpaces(sentencesArray);
    free(sentencesArray->sentences[sentencesArray->len-- -1]); // Удаление последнего предложения из структуры 
    if (function != 0) {
        function(sentencesArray);
    }
    
    return 0;

}