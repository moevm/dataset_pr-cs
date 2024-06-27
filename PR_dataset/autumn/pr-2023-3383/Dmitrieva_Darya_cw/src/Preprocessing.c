#include "structs.h"
#include "Preprocessing.h"
struct Sentence* readSentence() {
    size_t size = STEP;
    wchar_t* buf = malloc(size * sizeof(wchar_t));
    if (!buf) {
        wprintf(L"Memory allocation failed!\n");
        return NULL;
    }

    size_t n = 0; 
    wchar_t temp;
    do {
        if (n + 2 >= size) { 
            wchar_t* t = realloc(buf, (size + STEP) * sizeof(wchar_t));
            if (!t) {
                wprintf(L"Memory allocation failed!\n");
                free(buf);
                return NULL;
            }
            size += STEP;
            buf = t;
        }
        temp = (wchar_t)getwchar(); 
        if (temp == WEOF) {
            break;
        }

        if (n == 0) {
            if (temp == L'\t' || temp == L' ') {
                continue;
            } else if (temp == L'\n') {
                temp = (wchar_t)getwchar(); 
                if (temp == L'\n') {
                    free(buf);
                    return NULL;
                }
            }
        }
        buf[n] = temp; 
        n++;
    } while (temp != L'.' && temp != WEOF); 
    buf[n] = L'\0';


    struct Sentence* sentence = malloc(sizeof(struct Sentence));
    if (!sentence) {
        wprintf(L"Memory allocation failed!\n");
        free(buf);
        return NULL;
    }
    sentence->str = buf;
    sentence->size = n;
    return sentence;
}


struct Text readText() {
    size_t size = STEP;
    struct Sentence** text = malloc(size * sizeof(struct Sentence*));
    if (!text) {
        wprintf(L"Memory allocation failed!\n");
        return (struct Text){NULL, 0, 0};
    }

    size_t n = 0;
    struct Sentence* temp;
    do {
        temp = readSentence();

        if (temp == NULL) {
            break;
        }

        if (n >= size) {
            size *= 2;
            struct Sentence** t = realloc(text, size * sizeof(struct Sentence*));
            if (!t) {
                wprintf(L"Memory allocation failed!\n");
                for (size_t i = 0; i < n; i++) {
                    free(text[i]->str);
                    free(text[i]);
                }
                free(text);
                free(temp);
                return (struct Text){NULL, 0, 0};
            }
            text = t;
        }

        text[n] = temp;
        n++;
    } while (true);

    struct Text txt;
    txt.size = size;
    txt.sents = text;
    txt.n = n;
    txt.shouldFree = true;
    return txt;
}

struct Text func_obr_text(struct Text text) {
    struct Sentence** new_sents = (struct Sentence**) malloc(sizeof(struct Sentence*) * text.size);
    if (new_sents == NULL) {
        wprintf(L"Error: not enough memory!");
        exit(0);
    }

    size_t count_new_sents = 0; // Счетчик новых предложений
    int flag;

    for (size_t i = 0; i < text.n; i++) {
        flag = 0;
        for (size_t j = 0; j < count_new_sents; j++) {
            if (wcscasecmp(text.sents[i]->str, new_sents[j]->str) == 0) {
                flag = 1;
                break;
            }
        }
        if (flag == 0) {
            new_sents[count_new_sents] = text.sents[i];
            count_new_sents++;
        }
    }

    struct Text obr_text = {new_sents, count_new_sents, text.size, false};
    return obr_text;
}

