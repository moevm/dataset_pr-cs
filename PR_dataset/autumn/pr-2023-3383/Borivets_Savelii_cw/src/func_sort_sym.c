#include "func_sort_sym.h"
#include "struct.h"

int compare(const void* a, const void* b) {
    const wchar_t* ch1 = (const wchar_t*)a;
    const wchar_t* ch2 = (const wchar_t*)b;
    return -wcscmp(ch1, ch2);
}

struct Text func_sort_sym(struct Text text) {
    wchar_t **sym_text = (wchar_t **) malloc(sizeof(wchar_t*) * text.cnt_sen);
    //wchar_t *sym_sen = (wchar_t *) malloc(sizeof(wchar_t) * wcslen(text.txt[0]));
    for (size_t i = 0; i < text.cnt_sen; i++) {
        wchar_t *sym_sen = (wchar_t *) malloc(sizeof(wchar_t) * wcslen(text.txt[i]));
        size_t count_sym = 0;
        for (size_t j = 0; j < wcslen(text.txt[i]); j++) {
            if (wcschr(L"№*$#@", text.txt[i][j])) {
                sym_sen[count_sym] = text.txt[i][j];
                count_sym++;
            }
            sym_sen[count_sym] = '\0';
        }
        qsort(sym_sen, count_sym, sizeof(wchar_t), compare);
        sym_text[i] = sym_sen;
    }
    struct Text all_sym_text = {sym_text, text.cnt_sen};
    return all_sym_text;
}