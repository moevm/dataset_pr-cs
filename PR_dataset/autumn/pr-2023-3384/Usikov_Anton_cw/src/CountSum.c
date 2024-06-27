#include "CountSum.h"

void CountSumSent(struct Sentence* S) {
    wchar_t* str = S->str;
    int len = S->l;

    
    int j = -1;
    int i2 = 0;
    int sum = 0;

    for (int i = 0; i < len; i++) {
        i2 = i;
        int N = 0;
        if (iswdigit(str[i])) {

            while (iswdigit(str[i2]) && i2 < len) {
                i2++; j++;
            }
            while (j >= 0){
                N += (str[i]-'0')*pow(10, j--);
                i ++;
            }
            sum += N;
        }         
    }
    wprintf(L"%d\n", sum);
}

void CountSum(struct Text* text) {
    struct Sentence** txt = text->txt;
    int textLength = text->l;

    for (int i = 0; i < textLength; i++) {
        struct Sentence* sentence = txt[i];
        CountSumSent(sentence);
    }
}
