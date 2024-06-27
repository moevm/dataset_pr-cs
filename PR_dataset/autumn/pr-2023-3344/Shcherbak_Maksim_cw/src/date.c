#include <stdlib.h>
#include <wchar.h>

#include "structures.h"
#include "printFunctions.h"

void add_date_to_sentence(struct Sentence *sentence, int day, int month, int year) {
    wchar_t* formatted_date = malloc(11 * sizeof(wchar_t));
    swprintf(formatted_date, 11, L"%02d-%02d-%04d", day, month, year);
    wchar_t* sentence_with_date = malloc((sentence->len + 12) * sizeof(wchar_t)); // +12 для даты и разделителя

    wcscpy(sentence_with_date, sentence->sentence); // копируем исходное предложение
    wcscat(sentence_with_date, L" "); // добавляем пробел
    wcscat(sentence_with_date, formatted_date); // добавляем дату

    free(sentence->sentence);
    free(formatted_date);

    sentence->sentence = sentence_with_date;
    sentence->len += 12; // увеличиваем длину предложения на размер даты и разделителя
}

void data(struct Text *text) {
    for (int i = 0; i < text->len; ++i) {
        int wordsCount = 0;
        int maxLength = 0;
        int totalLength = 1;

        struct Sentence *sentence = text->sentences[i];
        wchar_t* pred = sentence->sentence;
        totalLength += wcslen(pred);
        wchar_t* pt;
        wchar_t* pwc = wcstok(pred, L" ,.-:;", &pt);
        
        while (pwc != NULL) {
            wordsCount++;
            int length = wcslen(pwc);
            if (length > maxLength) {
                maxLength = length;
            }
            // totalLength += length;

            pwc = wcstok(NULL, L" ,.-:;", &pt);
        }
        int day = wordsCount;
        int month = maxLength;
        int year = totalLength + 1900;

        add_date_to_sentence(sentence, day, month, year);
    }
}
