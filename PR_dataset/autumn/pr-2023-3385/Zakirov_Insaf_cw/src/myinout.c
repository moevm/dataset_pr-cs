#include "myinout.h"
#include "mysupport.h"

void printinfo() {
    wprintf(L"Course work for option %s, created by %s %s.\n", OPTION, NAME, SURNAME);
}

void printhelp() {
    wprintf(L"1 - num of sentence and diff system time and segments like hours:minutes\n");
    wprintf(L"2 - delete all upper case latin letters\n");
    wprintf(L"3 - reverse sort on count cyrillic letters\n");
    wprintf(L"4 - delete sentences with special symbols (№*$#@)\n");
}

void printallocerror(char* func, char* var, char* alloctype) {
    wprintf(L"Error: can't %s data for %s in %s\n", alloctype, var, func);
}

void printerror(char* message) {
    wprintf(L"Error: %s\n", message);
}

void printtext(Text* result) {
    for (int i = 0; i < (*result).count; ++i) {
        for (int j = 0; j < (*result).sentence[i].count; ++j) {
            wprintf(L"%lc", (*result).sentence[i].symbol[j]);
        }
        wprintf(L"\n");
    }
}

void printf1(int num, int diff) {
    wprintf(L"%d - %d\n", num, diff);
}

int scancommand() {
    int choice;
    wscanf(L"%d", &choice);
    
    return choice;
}

void scantext(Text* text) {
    int is_error = 0;

    inittext(text);
    int countblocks = 0;

    int ready_end = 0;
    int start_sentence = 0;

    while(1) {
        wint_t c = getwchar();

        if (c == L'\n') {
            if (ready_end) {
                break;
            } else {
                ready_end = 1;
                continue;
            }
        } else {
            ready_end = 0;
        }

        if (c != L' ') {
            start_sentence = 1;
        } else if (!start_sentence) {
            continue;
        }

        text->sentence[text->count].symbol[text->sentence[text->count].count] = c;
        text->sentence[text->count].count++;
        text->sentence[text->count].symbol = (wchar_t*) realloc(text->sentence[text->count].symbol, (text->sentence[text->count].count + 1) * sizeof(wchar_t));


        if (text->sentence[text->count].count >= BLOCK * countblocks) {
            countblocks++;
            text->sentence[text->count].symbol = (wchar_t*) realloc(text->sentence[text->count].symbol, (BLOCK * countblocks + 1) * sizeof(wchar_t));
        } 


        if (text->sentence[text->count].symbol == NULL) {
            printallocerror("scantext", "symbol", "realloc");
            is_error = 1;
            break;
        }

        if (c == L'.') {
            text->count++;
            text->sentence = (Sentence*) realloc(text->sentence, (text->count + 1) * sizeof(Sentence));
            
            if (text->sentence == NULL) {
                printallocerror("scantext", "sentence", "realloc");
                is_error = 1;
                break;
            }
            
            text->sentence[text->count].count = 0;
            text->sentence[text->count].symbol = (wchar_t*) malloc((text->sentence[text->count].count + 1) * sizeof(wchar_t));

            if (text->sentence[text->count].symbol == NULL) {
                printallocerror("scantext", "symbol", "malloc");
                is_error = 1;
                break;
            }

            start_sentence = 0;
        }
    }
    
    if (!is_error) {
        mydelete(text);
    } else {
        myfreetext(text);
        exit(1);
    }

}
