#include "Common.h"
#include "Function2.h"

void reverseWordsInSentences(char **text) {
 for (int i = 0; text[i] != NULL; i++) {
 int len_str = strlen(text[i]); // Длина строки
 int start = 0; // Начало слова
 int fl = 0; // Флаг нахождения буквы после разделителя

 for (int j = 0; j <= len_str; j++) { // Используем 'j', чтобы избежать конфликта с внешним циклом
 // Начинаем слово, когда встречаем буквенно-цифровой символ после разделителя
 if ((fl == 0) && (isalnum(text[i][j]))) {
 start = j;
 fl = 1;
 }

 // Конец слова может быть определён различными символами, также проверяем, что предыдущий символ - буквенно-цифровой
 if (((text[i][j] == ',') || (text[i][j] == ' ') || (text[i][j] == '.') || (text[i][j] == '\0')) && (isalnum(text[i][j - 1]))) {
 int stop = j - 1;

 // Переворачиваем слово между 'start' и 'stop'
 for (int k = start, l = stop; k < l; k++, l--) {
 char temp = text[i][k];
 text[i][k] = text[i][l];
 text[i][l] = temp;
 }
 fl = 0; // Сбрасываем флаг для поиска следующего слова
 }
 }
 }
}
