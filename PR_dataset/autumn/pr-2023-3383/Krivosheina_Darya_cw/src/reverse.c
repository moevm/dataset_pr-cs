#include "reverse.h"
#include "struct.h"


void reverse(wchar_t *sent){
    int cap_word = WORD, cap_other = OTHER; // переменные capacity для расширения памяти в массивах блоками
    int len_word = 0, len_other = 0; // длины массивов
    wchar_t *word = malloc(cap_word * sizeof(wchar_t));  // массив для текущего считываемого слова
    wchar_t *other = malloc(cap_other * sizeof(wchar_t)); // массив для текущей считываемой пунктуации
    for (int w1 = wcslen(sent) - 2; w1 >= 0; w1--){  
        if (sent[w1] != ' ' && sent[w1] != ',' && sent[w1] != '.' && sent[w1] != '\n'){ // проверка на то, является ли считанный символ буквой
            if (len_word % (WORD - 1) == 0 && len_word != 0){  // расширение памяти для слова в случае необходимости 
                    cap_word += WORD;
                    word = realloc(word, cap_word * sizeof(wchar_t));
                }
            word[len_word] = sent[w1];
            len_word++;
            if (sent[w1 - 1] == ' ' || sent[w1 - 1] == ',' || w1 == 0 || sent[w1 - 1] == '\n'){ // проверка на то, является ли считанный символ первой буквой слова
                for (int y = len_word - 1; y >= 0; y--){  // вывод считанного массива слова задом наперед (таким образом каждое слово выводится обычным образом, но первым выводится последнее, а последним - первое)
                    wprintf(L"%lc", word[y]);
                }
                memset(word, 0, sizeof(word)); // обнуление массива слова и всех его показателей
                len_word = 0;
                cap_word = WORD;
            }
        } else {  // считывание пунктуации
            if (len_other % (OTHER - 1) == 0){ 
                cap_other += OTHER;
                other = realloc(other, cap_other * sizeof(wchar_t));
            }
            other[len_other] = sent[w1];
            len_other++;
            if ((sent[w1] == ',' || sent[w1] == ' ' || sent[w1] == '\n') && sent[w1 - 1] != ',' && sent[w1 - 1] != ' ' && sent[w1 - 1] != '\n'){ // поиск начала пунктуации сразу после слова
                for (int y1 = len_other - 1; y1 >= 0; y1--){  // вывод считанного массива пунктуации задом наперед
                    wprintf(L"%lc", other[y1]);
                }
                memset(other, 0, sizeof(other)); // обнуление массива пунктуации и всех его показателей
                len_other = 0;
                cap_other = OTHER;
            }
        }
    }
    wprintf(L".\n");
}
