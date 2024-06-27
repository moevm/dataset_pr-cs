#ifndef INPUTFUNCS_H
#define INPUTFUNCS_H
char** strs_input(int* counter);
int is_sentence_repeated(char* sentence1, char* sentence2);
void strs_preprocessing(char** sentences, int* sentencesnum);
#endif