#include "func_cw.h"
#include "struct.h"

struct Text func_cw(struct Text text) {
    size_t count_sen = 0, N, count_ch = 0;
    wchar_t **double_text = (wchar_t **) malloc(sizeof(wchar_t*) * text.cnt_sen);
    for (size_t i = 0; i < text.cnt_sen; i++) {
        N = wcslen(text.txt[i]);
        wchar_t *sen = (wchar_t *) malloc(sizeof(wchar_t) * N * 5);
        count_ch = 0;
        wchar_t *word = (wchar_t *) malloc(sizeof(wchar_t) * N);
        int w_cnt = 0;
        for (size_t j = 0; j < wcslen(text.txt[i]); j++) {
            if (text.txt[i][j] == ' ') {
                sen[count_ch] = '\0';
                word[w_cnt] = ' ';
                w_cnt++;
                word[w_cnt] = '\0';
                count_ch += wcslen(word);
                wcscat(sen, word);
                count_ch += wcslen(word);
                wcscat(sen, word);
                free(word);
                wchar_t *word = (wchar_t *) malloc(sizeof(wchar_t) * N);
                w_cnt = 0;
            } else if (text.txt[i][j] == '.') {
                sen[count_ch] = '\0';
                word[w_cnt] = ' ';
                w_cnt++;
                word[w_cnt] = '\0';
                count_ch += wcslen(word);
                wcscat(sen, word);
                word[w_cnt - 1] = '.';
                count_ch += wcslen(word);
                wcscat(sen, word);
                free(word);
                wchar_t *word = (wchar_t *) malloc(sizeof(wchar_t) * N);
                w_cnt = 0;
            } else {
                word[w_cnt] = text.txt[i][j];
                w_cnt++;
            }
        }
        double_text[i] = sen;
        count_sen++;
    }
    struct Text new_text = {double_text, count_sen};
    return new_text;
}