#include "func_translit.h"
#include "struct.h"

int indkir(wchar_t ch) {
    if (1040 <= ch && ch <= 1103) {
        return (int) ch - 1040;
    } else if (ch == 1025) {
        return 64;
    } else if (ch == 1105) {
        return 65;
    } else {
        return -1;//если буква не кириллическая
    }
}

struct Text func_translit(struct Text text) {
    wchar_t *alf_eng[] = {L"A\0", L"B\0", L"V\0", L"G\0", L"D\0", L"E\0", L"Zh\0", L"Z\0", L"I\0", L"J\0", L"K\0", L"L\0", L"M\0", L"N\0", L"O\0", L"P\0", L"R\0", L"S\0", L"T\0", L"U\0", L"F\0", L"X\0", L"Cz\0", L"Ch\0", L"Sh\0", L"Shh\0", L"``\0", L"Y`\0", L"`\0", L"E`\0", L"Yu\0", L"Ya\0", L"a\0", L"b\0", L"v\0", L"g\0", L"d\0", L"e\0", L"zh\0", L"z\0", L"i\0", L"j\0", L"k\0", L"l\0", L"m\0", L"n\0", L"o\0", L"p\0", L"r\0", L"s\0", L"t\0", L"u\0", L"f\0", L"x\0", L"cz\0", L"ch\0", L"sh\0", L"shh\0", L"``\0", L"y`\0", L"`\0", L"e`\0", L"yu\0", L"ya\0", L"Yo\0", L"yo\0"};
    wchar_t **trans_text = (wchar_t **) malloc(sizeof(wchar_t*) * text.cnt_sen);
    wchar_t *trans_sen = (wchar_t *) malloc(sizeof(wchar_t) * wcslen(text.txt[0]));
    int flag;
    size_t count_ch, N;
    for (size_t i = 0; i < text.cnt_sen; i++) {
        N = wcslen(text.txt[i]);
        trans_sen = (wchar_t *) malloc(sizeof(wchar_t) * N);
        count_ch = 0;
        int len_sen = wcslen(text.txt[i]);
        for (size_t j = 0; j < len_sen; j++) {
            int ind_let = indkir(text.txt[i][j]);
            if (ind_let != -1) {
                int len_let = wcslen(alf_eng[ind_let]);
                if (count_ch + len_let >= N - 1) {
                    N += 50;
                    trans_sen = (wchar_t *) realloc(trans_sen, sizeof(wchar_t) * N);
                }
                for (size_t k = 0; k < len_let; k++) {
                    trans_sen[count_ch] = alf_eng[ind_let][k];
                    count_ch++;
                }
            } else {
                if (flag) {
                    if (count_ch == N - 1) {
                        N += 50;
                        trans_sen = (wchar_t *) realloc(trans_sen, sizeof(wchar_t) * N);
                    }
                    trans_sen[count_ch] = text.txt[i][j];
                    count_ch++;
                }
            }
        }
        trans_sen[count_ch] = '\0';
        trans_text[i] = trans_sen;
    }
    struct Text translit_text = {trans_text, text.cnt_sen};
    return translit_text;
}