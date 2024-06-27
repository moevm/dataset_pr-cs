#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define ERROR_INSTRUCTION_NOTHING_ENTERED "Error: Incorrect instruction entered, you didn't enter anything."
#define ERROR_INSTRUCTION_INCORRECT_INPUT "Error: You entered the number incorrectly, enter 0,1,2,3,4 or 5 next time."
#define ERROR_TEXT_EMPTY_SENTENCE "Error: Incorrect text entered, you have entered an empty sentence."
#define ERROR_TEXT_INCORRECT_SYMBOL "Error: Incorrect text entered, tab or new line was added between words or sentences."
#define ERROR_TEXT_DOT_MISSING "Error: Incorrect text entered, you forgot to put a dot at the end of the sentence."
void print_text_after_work(char** sentences, int last_sentence_index){
    for (int ind_sentence = 0; ind_sentence < last_sentence_index; ind_sentence++)
    {
        printf("%s\n", sentences[ind_sentence]);
    }
}
void print_error(int error_num){
    if (error_num == 1){
        printf("%s\n",ERROR_INSTRUCTION_NOTHING_ENTERED);
        exit(EXIT_FAILURE);
    }
    else if (error_num == 2){
        printf("%s\n",ERROR_INSTRUCTION_INCORRECT_INPUT);
        exit(EXIT_FAILURE);
    }
    else if (error_num == 3){
        printf("%s\n",ERROR_TEXT_EMPTY_SENTENCE);
        exit(EXIT_FAILURE);
    }
    else if (error_num == 4){
        printf("%s\n",ERROR_TEXT_INCORRECT_SYMBOL);
        exit(EXIT_FAILURE);
    }else if (error_num == 5){
        printf("%s\n",ERROR_TEXT_DOT_MISSING);
        exit(EXIT_FAILURE);
    }
}
