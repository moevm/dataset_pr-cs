#ifndef INIT_PROC_TEXT_H
#define INIT_PROC_TEXT_H
char *inputText(); // ввод текста
void printHelp(); //вывод справки
char **splitSentences(char *text, int *count_sent); // разделение предложений на предложения
char **deleteRepeatSentences(char **int_sentences, int *count); //удаляет повторяющиеся предложения
void printSentences(char** sentences, int *count); // выводит предложения и очищает память
char *strlower(char *sentence); // возвращает строчный вид предложения
#endif