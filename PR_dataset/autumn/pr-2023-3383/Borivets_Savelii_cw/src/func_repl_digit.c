#include "func_repl_digit.h"
#include "struct.h"

struct Text func_repl_digit(struct Text text) {
    size_t count_sen = 0, N, count_ch = 0;
    wchar_t **repl_text = (wchar_t **) malloc(sizeof(wchar_t*) * text.cnt_sen);
    for (size_t i = 0; i < text.cnt_sen; i++) {
        N = wcslen(text.txt[i]);
        wchar_t *repl_sen = (wchar_t *) malloc(sizeof(wchar_t) * N);
        count_ch = 0;
        for (size_t j = 0; j < wcslen(text.txt[i]); j++) {
            if (count_ch >= N - 5) {
                N += 50;
                repl_sen = (wchar_t *) realloc(repl_sen, sizeof(wchar_t) * N);
            }
            if (text.txt[i][j] == L'2') {
                wcscat(repl_sen, L"10\0");
                count_ch += 2;
            } else if (text.txt[i][j] == L'3') {
                wcscat(repl_sen, L"11\0");
                count_ch += 2;
            } else if (text.txt[i][j] == L'4') {
                wcscat(repl_sen, L"100\0");
                count_ch += 3;
            } else if (text.txt[i][j] == L'5') {
                wcscat(repl_sen, L"101\0");
                count_ch += 3;
            } else if (text.txt[i][j] == L'6') {
                wcscat(repl_sen, L"110\0");
                count_ch += 3;
            } else if (text.txt[i][j] == L'7') {
                wcscat(repl_sen, L"111\0");
                count_ch += 3;
            } else if (text.txt[i][j] == L'8') {
                wcscat(repl_sen, L"1000\0");
                count_ch += 4;
            } else if (text.txt[i][j] == L'9') {
                wcscat(repl_sen, L"1001\0");
                count_ch += 4;
            } else {
                repl_sen[count_ch] = text.txt[i][j];
                count_ch++;
            }
            repl_sen[count_ch] = '\0';
        }
        repl_text[i] = repl_sen;
        count_sen++;
    }
    struct Text new_text = {repl_text, count_sen};
    return new_text;
}