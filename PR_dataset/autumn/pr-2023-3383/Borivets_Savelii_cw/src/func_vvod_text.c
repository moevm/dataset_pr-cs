#include "func_vvod_text.h"
#include "struct.h"

struct Text func_vvod_text() {
    size_t count_sen = 0, M = 20;
    wchar_t **text = (wchar_t **) malloc(sizeof(wchar_t*) * M);
    wchar_t ch;
    for (size_t i = 0;; i++) {
        size_t N = 50, count_ch = 0;
        int flag = 0;//флаг для \n
        while (wcschr(L"\n\t \0", ch = getwchar())) {
            if (ch == '\n') {
                if (flag) {
                    struct Text vvod_text = {text, count_sen};
                    return vvod_text;//<----Конец ввода
                }
                flag = 1;
            } else flag = 0;
        }
        wchar_t *sen = (wchar_t *) malloc(sizeof(wchar_t) * N);
        for (size_t j = 0; ch != '.'; j++) {
            flag = 0;
            sen[j] = ch;
            count_ch++;
            if (count_ch >= N - 1) {
                N += 50;
                sen = (wchar_t *) realloc(sen, sizeof(wchar_t) * N);
            }
            ch = getwchar();
        }
        sen[count_ch] = '.';
        count_ch++;
        if (count_ch >= N - 1) {
            N += 50;
            sen = realloc(sen, sizeof(wchar_t) * N);
        }
        sen[count_ch] = '\0';
        text[i] = sen;
        count_sen++;
        if (count_sen >= M - 1) {
            M += 20;
            text = realloc(text, sizeof(wchar_t*) * M);
        }
    }
}