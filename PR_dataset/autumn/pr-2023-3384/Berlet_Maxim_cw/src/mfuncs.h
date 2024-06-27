#ifndef MFUNCS_H
#define MFUNCS_H
void replace_repeated_let(char* str, int counter);
char** del_sent(char** sentences, int* sentencesnum);
void first_and_last_word_lencounter(const char* sentence, int res[2]);
int comparator(const void* str1, const void* str2);
int count_words(char* sentence);
int is_mul_three(char* sentence);
#endif