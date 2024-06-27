#include "delete.h"
#include "struct.h"

wchar_t* delete(wchar_t *sent){
    int flag = 0;  // проверка на то, короче ли все слова трех 
    int len_word = 0;
    for (int q = 0; q < wcslen(sent) - 1; q++){
        if (sent[q] != ' ' && sent[q] != ','  && sent[q] != '.' && sent[q] != '\n'){  // проверка на то, является ли символ буквой
            len_word++;
            if (sent[q - 1] == ' ' || sent[q - 1] == ','  || sent[q - 1] == '.' || sent[q - 1] == '\n' || q == 0){ // проверка на начало слова
                len_word = 1;
            } 
            if (sent[q + 1] == ' ' || sent[q + 1] == ','  || sent[q + 1] == '.' || sent[q + 1] == '\n'){  // проверка на конец слова
                if (len_word > 3){  // проверка на длину слова
                    flag = 1;  // изменение флага, если слово длиннее трех
                    break;
                }
            }
        }
    }
    if (flag == 0){  // если флаг не изменился - слово не подходит 
        sent = L"0"; // изменение строки на 0
    }
    return sent;
}
