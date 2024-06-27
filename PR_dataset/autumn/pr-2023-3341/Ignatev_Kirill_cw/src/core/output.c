#include <stdio.h>

#include "../header/only_num.h"
#include "../header/sort_strings_by_uppercase_count.h"
#include "../header/del_sent_by_word.h"
#include "../header/replace_digits_with_words.h"
#include "../header/output.h"
#include "../header/defence.h"

#define AUTHOR_INFO "Course work for option 4.3, created by Kirill Ignatev."
#define PRINT_TEXT 0
#define ONLY_NUM 1
#define SORT_STRINGS_BY_UPPERCASE_COUNT 2
#define DEL_SENT_BY_WORD 3
#define REPLACE_DIGITS_WITH_WORDS 4
#define DEFENCE 9


void printAuthorInfo(){
    puts(AUTHOR_INFO);
}

void help() {
    printf("1)Output all sentences in which all words consist only of numbers.\n");
    printf("2)Sort sentences by reducing the number of capital letters in it.\n");
    printf("3)Delete all sentences in which the entered word appears two or more times\n");
    printf("4) Transform all sentences so that each occurrence of a digit is replaced by the corresponding substring (0 - \"Zero\", 1 - \"One\", 2 - \"Two\", etc.).\n");
}

void textOutput(int* sentences_number_before_changes, char** split_text){
    for (int i = 0; i < *sentences_number_before_changes; ++i) {
        if (split_text[i]!=NULL)
            printf("%s.\n", split_text[i]);
    }
}

void output(char* function_id, int* sentences_number_before_changes, char** split_text, char* keyword, char* keysentence){
    int case_number=*function_id-'0';
    switch (case_number) {
        case PRINT_TEXT:{
            textOutput(sentences_number_before_changes, split_text);
            break;
        }
        case ONLY_NUM:{
            onlyNum(split_text, sentences_number_before_changes);
            textOutput(sentences_number_before_changes, split_text);
            break;
        }
        case SORT_STRINGS_BY_UPPERCASE_COUNT:{
            sortStringsByUppercaseCount(split_text, sentences_number_before_changes);
            textOutput(sentences_number_before_changes, split_text);
            break;
        }
        case DEL_SENT_BY_WORD:{
            delSentByWord(split_text, keyword, sentences_number_before_changes);
            textOutput(sentences_number_before_changes, split_text);
            break;
        }
        case REPLACE_DIGITS_WITH_WORDS:{
            replaceDigitsWithWords(split_text, sentences_number_before_changes);
            textOutput(sentences_number_before_changes, split_text);
            break;
        }
        case DEFENCE:{
            defence(split_text, sentences_number_before_changes, keysentence);
        }
    }
}
