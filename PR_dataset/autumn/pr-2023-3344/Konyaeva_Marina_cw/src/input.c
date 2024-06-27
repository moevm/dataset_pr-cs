#include "input.h"


struct Sentence *readSentence() {
    int size = MEM_STEP;
    int is_sent_start = 1;
    int n = 0;
    int nlcount = 0;
    wchar_t *buf = (wchar_t *) malloc(size * sizeof(wchar_t));
    wchar_t temp;
    do {
        if (n >= size - 2) {
            size += MEM_STEP;
            wchar_t *t = (wchar_t *) realloc(buf, (size) * sizeof(wchar_t));
            if (!t) {
                wprintf(L"Ошибка, не удается выделить память!\n");
                free(t);
                exit(1);
            }else {
                buf = t;
            }
        }
        temp = (wchar_t)getwchar();
        if (is_sent_start) {
            if (temp == ' ' || temp=='\t') {
                continue;
            } else {
                is_sent_start = 0;
            }
        }
        if(temp == L'\n'){
            nlcount++;
        }else{
            nlcount = 0;
        }
        buf[n] = temp;
        n++;
    } while ((nlcount < 2) && (temp != L'.'));
    buf[n++] = L'\0';
    struct Sentence *sent = (struct Sentence *) malloc(sizeof(struct Sentence));
    sent->str = buf;
    sent->len = n;
    sent->size = size;
    wchar_t* s = (wchar_t *) malloc((sent->len+1)* sizeof(wchar_t));
    wcscpy(s,buf);
    int countwords = 0;
    wchar_t *pt;
    wchar_t *pch = wcstok(s,SEPARATORS,&pt);
    while (pch!=NULL){
        countwords++;
        pch = wcstok(NULL,SEPARATORS,&pt);
    }
    sent->countwords = countwords;
    return sent;
}
struct Text readText() {
    int size = MEM_STEP;
    struct Sentence **text = (struct Sentence **) malloc(size * sizeof(struct Sentence *));
    int n = 0;
    struct Sentence *temp;
    int endpoint = 1;
    do{
        if (n >= size - 1) {
            size+=MEM_STEP;
            struct Sentence **t = (struct Sentence **) realloc(text, size * sizeof(struct Sentence*));
            if (!t) {
                wprintf(L"Ошибка, не удается выделить память!\n");
                free(t);
                exit(0);
            }else {
                text = t;
            }
        }
        temp = readSentence();
        if (wcsstr(temp->str, L"\n\n")) {
            endpoint--;
            free(temp);
        } else {
            temp->len = wcslen(temp->str);
            text[n]=temp;
            n++;
        }
    }while(endpoint);
    struct Text txt;
    txt.size = size;
    txt.array = text;
    txt.n = n;
    return txt;
}
int Repeating(wchar_t *sent1,wchar_t *sent2){
    int flag=1;
    if (wcslen(sent1)==wcslen(sent2)) {
        for (int a = 0; a < wcslen(sent1); a++) {
            if (towlower(sent1[a]) != towlower(sent2[a])) {
                flag = 0;
                break;
            }
        }
    }else{
        flag = 0;
    }
    if (flag){
        return 0;
    }
    return 1;
}
void format (struct Text *t){
    for (int i = 0; i < t->n - 1; i++){
        if (t->array[i]->str[0] == L'.') {
            free(t->array[i]);
            memmove(&t->array[i], &t->array[i + 1], (sizeof(struct Sentence *) * (t->n - i - 1)));
            t->n -= 1;
        }
        for (int j = i+1; j < t->n; j++) {
            if (Repeating(t->array[i]->str, t->array[j]->str) == 0) {
                free(t->array[j]);
                memmove(&t->array[j], &t->array[j + 1], sizeof(struct Sentence *) * (t->n - j - 1));//размер
                t->n -= 1;
                j -= 1;
            }
        }
    }
    for (int i = 0; i < t->n; i++){
        if (t->array[i]->str[0] == L'\n') {
            wmemmove(&t->array[i]->str[0], &t->array[i]->str[1], (t->array[i]->len));
            t->array[i]->len = t->array[i]->len-1;
        }
    }
}


