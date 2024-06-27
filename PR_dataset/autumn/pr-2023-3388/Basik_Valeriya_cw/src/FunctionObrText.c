#include "Common.h"
#include "FunctionObrText.h"

void functionObrText(char** text, int* count_sentence) {
 for (int i = 0; i < *count_sentence; i++) {
 if (text[i] == NULL) {
 // Проверка на NULL для текущей строки
 continue;
 }

 for (int j = i + 1; j < *count_sentence; j++) {
 if (text[j] == NULL) {
 // Проверка на NULL для сравниваемой строки
 continue;
 }

 if (strcasecmp(text[i], text[j]) == 0) {
 free(text[j]);
 text[j] = NULL;

 for (int k = j; k < *count_sentence - 1; k++) {
 text[k] = text[k + 1];
 }

 text[*count_sentence - 1] = NULL;
 (*count_sentence)--;
 j--;
 }
 }
 }
}
