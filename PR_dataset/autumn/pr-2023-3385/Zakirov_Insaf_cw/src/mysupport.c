#include "mysupport.h"
#include "myinout.h"

void mydelete(Text* text) {
    int count = text->count;
    for (int i1 = count - 1; i1 > 0; --i1) {
        for (int i2 = i1 - 1; i2 >= 0; --i2) {
            int equal = 0;
            for (int j = 0; j < text->sentence[i1].count; ++j) {
                if (text->sentence[i1].count == text->sentence[i2].count) {
                    if (towlower(text->sentence[i1].symbol[j]) == towlower(text->sentence[i2].symbol[j])) {
                        equal++;
                    }
                }
            }

            if (equal == text->sentence[i1].count) {
                myfreesentence(&(text->sentence[i1]));
                for (int j = i1; j < text->count - 1; ++j) {
                    text->sentence[j] = text->sentence[j + 1];
                }

                text->sentence = (Sentence*) realloc(text->sentence, text->count * sizeof(Sentence));
                text->count--;
            }
        }
    } 
}

void myfreesentence(Sentence* sentence) {
    free(sentence->symbol);
}

void myfreetext(Text* text) {
    int count = text->count;

    for (int i = count - 1; i >= 0; --i) {
        myfreesentence(text->sentence + i);
    }
    free(text->sentence);
}

void mycheckerror(const void* p, char* func, char* var, char* alloctype) {
    if (p == NULL) {
        printallocerror(func, var, alloctype);
    }
}

int mygethour(const Sentence* sen, const int start, int* hour) {
    int mult = 1;
    for (int i = start - 1; i >= 0; --i) {
        if (iswdigit(sen->symbol[i])) {
            *hour += mult * (sen->symbol[i] - L'0');
            mult *= 10;
        } else {
            if (i == start - 1) {
                return 0;
            } else {
                return 1;
            }
        }
    }
}

int mygetminute(const Sentence* sen, const int start, int* minute) {
    int mult = 10;
    for (int i = start + 1; i < sen->count; ++i) {
        if (iswdigit(sen->symbol[i])) {
            *minute = *minute * mult + (sen->symbol[i] - L'0');
        } else {
            if (i == start + 1) {
                return 0;
            } else {
                return 1;
            }
        }
    }
}

int myisupper(wchar_t c) {
    return (c >= L'A' && c <= L'Z') ? 1 : 0;
}

int myiscyrillic(wchar_t c) {
    return (c >= L'а' && c <= L'я' || c >= L'А' && c <= L'Я') ? 1 : 0;
}

int countcir(Sentence* sentence) {
    int count = 0;
    for (int i = 0; i < sentence->count; i++){
        count += myiscyrillic(sentence->symbol[i]);
    }

    return count;
}

int compare(const void* a, const void* b) {
    Sentence *t_a = (Sentence*) a;
    Sentence *t_b = (Sentence*) b;

    return (countcir(t_b) - countcir(t_a));
}