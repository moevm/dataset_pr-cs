#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wchar.h>
#include <locale.h>

#include "../include/count_minutes.h"
#include "../include/remove_sentences.h"
#include "../include/replace_symbols.h"
#include "../include/sort_sentences.h"
#include "../include/text_processing.h"
#include "../include/struct.h"

void configureLetters() {
    setlocale(LC_ALL, "");
    fwide(stdout, 1);
    fwide(stdin, 1);
}

void prepareText(void (*func)(Text*)) {
    Text text;

    text = createText();
    readText(&text);
    
    clearText(&text);
    func(&text);

    printText(&text);
    freeText(&text);
}

void countAllMinutes(Text* text) {
    int seconds = 0;
    for (int i=0; i<text->real_size; i++)
        seconds += countMinutes(&text->sentences[i]);
    wprintf(L"%d минут %d секунд\n", seconds/60, seconds%60);
}

void replaceAllSymbols(Text* text) {
    for(int i=0; i<text->real_size; i++) {
        replaceSymbol(&text->sentences[i], L'%', L"<percent>");
        replaceSymbol(&text->sentences[i], L'#', L"<решетка>");
        replaceSymbol(&text->sentences[i], L'@', L"(at)");
    }
}

void printHelp() {
    wprintf(L"0 - Вывод текста после первичной обязательной обработки\n\
            \r1 - Посчитать и вывести в минутах количество секунд встречающихся в тексте. Количество секунд задается в виде подстроки “ <число> sec.\n\
            \r2 - Отсортировать предложения по увеличению сумме кодов символов первого слова в предложении.\n\
            \r3 - Заменить все символы \'%\', \'#\', \'@\' на \"<percent>\", \"<решетка>\", \"(at)\" соответственно.\n\
            \r4 - Удалить все предложения которые заканчиваются на слово с тремя согласными подряд.\n\
            \r5 - Вывод справки о функциях, которые реализует программа.\n");
}

void func(Text* text) {
    for (int i=0; i<text->real_size; i++) {
        wchar_t* sentence = wcsdup(text->sentences[i].sentence);

        int l = 0;
        int h = wcslen(sentence) - 1;
        int f = 0;

        for(int j=0; j < wcslen(sentence); j++) {
            while (sentence[j] == L' ' || sentence[j] == L'.' || sentence[j] == L',' || sentence[j] == L':' || sentence[j] == L';' || sentence[j] == L'\n') {
                j++;
            }

            while (sentence[h] == L' ' || sentence[h] == L'.' || sentence[h] == L',' || sentence[h] == L':' || sentence[h] == L';' || sentence[h] == L'\n') {
                h--;
            }

            if(sentence[j]>=L'А' && sentence[j]<=L'Я') sentence[j]+=L'я'-L'Я';
            if(sentence[h]>=L'А' && sentence[h]<=L'Я') sentence[h]+=L'я'-L'Я';

            if(sentence[j]>=L'A' && sentence[j]<=L'Z') sentence[j]+=L'z'-L'Z';
            if(sentence[h]>=L'A' && sentence[h]<=L'Z') sentence[h]+=L'z'-L'Z';

            if (sentence[j] != sentence[h]) {
                f = 1;
                break;
            }

            h--;
        }

        if ( f == 0 ) {
            if (text->sentences[i].sentence[0] == L'\n') {
                memmove(text->sentences[i].sentence, &text->sentences[i].sentence[1], sizeof(wchar_t)*wcslen(text->sentences[i].sentence));
                // wprintf(L"%ls\n", text->sentences[i].sentence);
            }
                wprintf(L"%ls\n", text->sentences[i].sentence);
            // else 
        }
    }
}

void processText() {
    int N;
    wscanf(L"%d", &N);
    Text text;

    switch(N) {
        case 0:
            prepareText(clearText);
            break;
        case 1:
            prepareText(countAllMinutes);
            break;
        case 2:
            prepareText(sortBySum);
            break;
        case 3:
            prepareText(replaceAllSymbols);
            break;
        case 4:
            prepareText(removeSentences);
            break;
        case 5:
            printHelp();
            break;
        case 9:
            text = createText();
            readText(&text);
            
            func(&text);

            // printText(&text);
            freeText(&text);
            break;
        default:
            fwprintf(stderr, L"Error: Invalid command number value.\n");
    }
}

int main() {
    configureLetters();
    wprintf(L"Course work for option 5.14, created by Vera Ermolaeva.\n");

    processText();
    return 0;
}