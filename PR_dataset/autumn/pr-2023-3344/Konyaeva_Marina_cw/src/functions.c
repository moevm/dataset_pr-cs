#include "functions.h"
#include "input.h"

void changeEnding(struct Text t){
    for (int i = 0; i < t.n;i++) {
        for (int j = 0; j < t.array[i]->len - 3; j++) {
            if ((towlower(t.array[i]->str[j]) == L'т')  && (towlower(t.array[i]->str[j+1]) == L'ь')  && (towlower(t.array[i]->str[j+2]) == L'с')  && (towlower(t.array[i]->str[j+3]) == L'я') ){
                wmemmove(&t.array[i]->str[j+1],&t.array[i]->str[j+2],(t.array[i]->len-j-1));
                t.array[i]->str[j] = L'т';
                t.array[i]->str[j+1]=L'с';
                t.array[i]->str[j+2]= L'я';
                t.array[i]->len = t.array[i]->len - 1;
                j+=3;
            }
            if ((towlower(t.array[i]->str[j]) == L'т')  && (towlower(t.array[i]->str[j+1]) == L'с')  && (towlower(t.array[i]->str[j+2]) == L'я') ){
            	t.array[i]->str = realloc(t.array[i]->str, (t.array[i]->len + 2) * sizeof(wchar_t));
                wmemmove(&t.array[i]->str[j+2],&t.array[i]->str[j+1],(t.array[i]->len-j-1));
                t.array[i]->str[j] = L'т';
                t.array[i]->str[j+1]=L'ь';
                t.array[i]->str[j+2]= L'c';
                t.array[i]->str[j+3]= L'я';
                t.array[i]->len = t.array[i]->len + 1;
            }
        }
    }
}
void moreTen(struct Text *t){
    int count = 0;
    for (int i = 0; i < t->n; i++){
        if (t->array[i]->countwords<=10){
            t->array[count]->str = t->array[i]->str;
            count++;
        }else{
            free(t->array[i]->str);
        }
    }
    t->n = count;
}
int cmp(const void *sent1,const void *sent2){
    struct Sentence *f = *(struct Sentence **) sent1;
    struct Sentence *s = *(struct Sentence **) sent2;
    int amount1 = f->countwords;
    int amount2 = s->countwords;
    if(amount1 < amount2)
        return -1;
    if (amount1 > amount2)
        return 1;
    return 0;
}

int greenWord(struct Text t){
    wchar_t *temp = (wchar_t *) malloc((t.array[0]->len + 1) * sizeof(wchar_t));
    wcscpy(temp, t.array[0]->str);
    wchar_t *pt;
    wchar_t *token = wcstok(temp, SEPARATORS, &pt);
    token = wcstok(NULL, SEPARATORS, &pt);
    if (token == NULL){
        return 0;
    }
    wchar_t ***words = arrofwords(t);
    wchar_t ***seps = arrofseps(t);
    for (int i = 0; i < t.n; i++){
        if (check(i, words, token, t)==1){
            for (int j = 0; j < t.array[i]->countwords; j++) {
                if (Repeating(words[i][j], token) == 0){
                    wprintf(L"%s%ls", GREEN, words[i][j]);
                }else {
                    wprintf(L"%s%ls", NONE, words[i][j]);
                }
                wprintf(L"%s%ls", NONE, seps[i][j]);

            }
            wprintf(L"\n");
            }
        }
    return 1;
}
int check(int i, wchar_t ***words, wchar_t *token, struct Text t){
    for (int j = 0; j < t.array[i]->countwords; j++){
        if (Repeating(words[i][j], token) == 0)
            return 1;
    }
    return 0;
}
void freeText(struct Text t) {
    for (int i = 0; i < t.n; i++) {
        free(t.array[i]->str);
        free(t.array[i]);
    }
}
wchar_t*** arrofwords(struct Text t){
    wchar_t ***words = malloc(sizeof(wchar_t *)*t.n);
    for (int i = 0; i < t.n; i++){
        words[i] = malloc(sizeof(wchar_t *) * t.array[i]->countwords);
        int countwords = 0;
        wchar_t *pt;
        wchar_t *temp = (wchar_t *) malloc((t.array[i]->len + 1) * sizeof(wchar_t));
        wcscpy(temp, t.array[i]->str);
        wchar_t *pch = wcstok(temp, SEPARATORS, &pt);
        while (pch!=NULL){
            words[i][countwords] = pch;
            words[i][countwords] = pch;
            countwords++;
            pch = wcstok(NULL, SEPARATORS, &pt);
        }
    }
    return words;
}
wchar_t*** arrofseps(struct Text t){
    wchar_t ***seps = malloc(sizeof(wchar_t *) * t.n);
    for (int i = 0;i < t.n;i++){
        seps[i] = malloc(sizeof(wchar_t *) * t.array[i]->countwords);
        int countseps = 0;
        wchar_t *pt;
        wchar_t *temp = (wchar_t *) malloc((t.array[i]->len + 1) * sizeof(wchar_t));
        wcscpy(temp, t.array[i]->str);
        wchar_t *pch = wcstok(temp, ALPHABET, &pt);
        while (pch!=NULL){
            seps[i][countseps] = pch;
            countseps++;
            pch = wcstok(NULL, ALPHABET, &pt);
        }
    }
    return seps;
}
void func6(struct Text t){
    wchar_t*** words = arrofwords(t);
    wchar_t*** seps = arrofseps(t);
    for (int i = 0; i < t.n; i++){
//        wchar_t* temp = malloc(sizeof(wchar_t) * (t.array[i]->len+1));
        wprintf(L"%ls",words[i][t.array[i]->countwords-1]);
        for (int j = t.array[i]->countwords-2; j >=0; j--){
            wprintf(L"%ls",seps[i][j]);
            wprintf(L"%ls",words[i][j]);
        }
        wprintf(L".\n");
    }
}

