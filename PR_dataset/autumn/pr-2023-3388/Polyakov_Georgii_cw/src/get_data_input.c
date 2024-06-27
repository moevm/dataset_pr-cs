#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "data_output.h"
#define INSTRUCTION_LEN 15
#define TEXT_LEN 150
#define BEFORE_ENTERING_INSTRUCTION "Please enter 0, 1, 2, 3, 4 or 5."
#define BEFORE_ENTERING_TEXT "Please enter a text consisting of sentences, each sentence must end with a dot."
int make_correct_sentences(char** sentences, int last_sentence_index){
    for (int ind_sentence = 0; ind_sentence<last_sentence_index; ind_sentence++){
        int flag_equality = 1;
        for (int ind_other_sentence = ind_sentence+1; ind_other_sentence<last_sentence_index; ind_other_sentence++){
            if (strlen(sentences[ind_sentence]) == strlen(sentences[ind_other_sentence])){
                int ind_symbol = 0;
                while (ind_symbol<strlen(sentences[ind_sentence]) && flag_equality){
                    if (tolower(sentences[ind_sentence][ind_symbol]) != tolower(sentences[ind_other_sentence][ind_symbol])){
                            flag_equality = 0;
                    }
                    ind_symbol++;
                }
                if (flag_equality == 1){
                    last_sentence_index--;
                    free(sentences[ind_other_sentence]);
                    memmove(&sentences[ind_other_sentence],&sentences[ind_other_sentence+1], (last_sentence_index-ind_other_sentence)*sizeof(char*));
                    ind_other_sentence--;
                }
            }
        }
    }
    return last_sentence_index;
}
int get_instruction_input(){
    char* instruction = malloc(INSTRUCTION_LEN);
    char instruction_letter = getchar();
    int last_letter_index = 0;
    int counter_for_realloc = 1;
    if (instruction_letter == '\n'){
        print_error(1);
    }
    while (instruction_letter!='\n'){
        if (last_letter_index == counter_for_realloc*INSTRUCTION_LEN-2){
            counter_for_realloc++;
            instruction = realloc(instruction, counter_for_realloc*INSTRUCTION_LEN*sizeof(char));
        }
        instruction[last_letter_index] = instruction_letter;
        last_letter_index++;
        instruction_letter = getchar();
    }
    instruction[strlen(instruction)] = '\0';
    for (int ind_symbol = 0; ind_symbol<last_letter_index; ind_symbol++){
        if(!(isdigit(instruction[ind_symbol]))){
            print_error(2);
        }
    }
    return atoi(instruction);

}

int get_text_input(char** sentences){
    char sentence_letter = getchar();
    int sentence_letter_index = 0;
    int last_sentence_index = 0;
    int flag_to_end_input = 1;
    int counter_for_realloc = 1;
    char* sentence = malloc(TEXT_LEN);
    char last_symbol;
    while (flag_to_end_input)
    {
        if (sentence_letter_index == counter_for_realloc*TEXT_LEN-2){
            counter_for_realloc++;
            sentence = realloc(sentence, counter_for_realloc*(TEXT_LEN)*sizeof(char));
        }
        if (!(sentence_letter_index == 0 && (sentence_letter == ' ' || sentence_letter == '\n'))){
            sentence[sentence_letter_index] = sentence_letter;
            sentence_letter_index++;
        }
        if(sentence_letter == '.'){
            if (sentence_letter_index == 1){
                print_error(3);
            }
            sentence[sentence_letter_index] = '\0';
            sentences[last_sentence_index] = sentence;
            sentence_letter_index = 0;
            sentence = malloc(TEXT_LEN);
            counter_for_realloc = 1;
            last_sentence_index++;
        }
        if (sentence_letter == '\n'){
            sentence_letter = getchar();
            if (sentence_letter == '\n'){
                flag_to_end_input = 0;
            }
        }else{
            last_symbol = sentence_letter;
            sentence_letter = getchar();
        }
    }
    if (last_symbol!='.'){
        print_error(5);
    }
    last_sentence_index = make_correct_sentences(sentences, last_sentence_index);
    return last_sentence_index;
}
