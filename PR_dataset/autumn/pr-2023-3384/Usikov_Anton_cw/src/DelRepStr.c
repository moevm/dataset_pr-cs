#include "DelRepStr.h"

void DelRepStr(struct Text* T) {
    for (int i = 0; i < T->l - 1; i++) 
    {
        struct Sentence* current = T->txt[i];

        if (current == NULL) {
            continue;
        }

        for (int j = i + 1; j < T->l; j++) {
            struct Sentence* compare = T->txt[j];

            if (compare == NULL) {
                continue;
            }

            if (wcscasecmp(current->str, compare->str) == 0) {
                T->txt[j] = NULL;
            }
        }
    }

    int newi = 0;
    for (int i = 0; i < T->l; i++) {
        if (T->txt[i] != NULL) {
            T->txt[newi] = T->txt[i];
            newi++;
        }
    }

    T->l = newi;
}
