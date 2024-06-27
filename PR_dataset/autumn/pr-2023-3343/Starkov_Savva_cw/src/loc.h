//
// Created by letewr on 09.12.23.
//

#ifndef CW_LOC_H
#define CW_LOC_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ROBIN "Robin"
#define BATMAN "I am Batman"
#define SIZEROBIN 6
#define SIZEBATMAN 11
char* get_text_Input();
int func_help(char* sentence);
char** func_9(char** text, int* sentence_number);
char** split_text(char* input_text,int* sentence_number,const char* splitters);
void remove_lead_spaces(char* str);
void print_func(char** text, int* sentence_number);
char** if_vowel(char** text, int* sentence_number);
char** split_to_number_sort(char** text, int* sentence_number);
char** sum_of_numbers_Sort(char** text, int* sentence_number);
char** delete_dublitacates(char** text,int* sentence_number);
void funny_func(int* sentence_number);
void robin_to_imBatman(char*** text,int* sentence_number);
#endif //CW_LOC_H
