#include "struct.h"
#include "sort.h"

int cmp(const void *a, const void *b){
    wchar_t *sent1 = *(wchar_t**)a;  // преобразование поданных переменных в необходимый тип
    wchar_t *sent2 = *(wchar_t**)b;
    int len_word1 = 0, len_word2 = 0; // длины первых слов первого и второго предложений
    for (int p1 = 0; p1 < wcslen(sent1); p1++){ //поиск длины первого слова первого предложения
        if (sent1[p1] != ' ' && sent1[p1] != ',' && sent1[p1] != '.' && sent1[p1] != '\n'){ // проверка на то, является ли буквой символ
            len_word1++;
            if (sent1[p1 + 1] == ' ' || sent1[p1 + 1] == ',' || sent1[p1 + 1] == '.' || sent1[p1 + 1] == '\n'){ // если следующий символ - не буква, то слово закончилось
                break;
            }
        }
    }
    for (int p2 = 0; p2 < wcslen(sent2); p2++){ //такой же алгоритм поиска первого слова второго предложения
        if (sent2[p2] != ' ' && sent2[p2] != ',' && sent2[p2] != '.' && sent2[p2] != '\n'){
            len_word2++;
            if (sent2[p2 + 1] == ' ' || sent2[p2 + 1] == ',' || sent2[p2 + 1] == '.' || sent2[p2 + 1] == '\n'){
                break;
            }
        }
    }
    return len_word1 - len_word2;
}

void sort(struct Text *full_text){
    qsort(full_text->text, full_text->len, sizeof(wchar_t*), cmp);
}
