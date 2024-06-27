#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "get_data_input.h"
#include "task_functions.h"
#include "data_output.h"
#define INSTRUCTION_LEN 15
#define TEXT_LEN 150
int main(){
    printf("Course work for option 4.14, created by Polyakov Georgii.\n");
    int instruction = get_instruction_input();
    char** sentences = (char**)malloc(TEXT_LEN*(sizeof(char*)));
    int last_sentence_index = 0;
    switch (instruction)
    {
    case 0:
        last_sentence_index = get_text_input(sentences);
        print_text_after_work(sentences, last_sentence_index);
        break;
    case 1:
        last_sentence_index = get_text_input(sentences);
        delete_all_numbers(sentences, last_sentence_index);
        print_text_after_work(sentences, last_sentence_index);
        break;
    case 2:
        last_sentence_index = get_text_input(sentences);
        is_palindrom(sentences, last_sentence_index);
        break;
    case 3:
        last_sentence_index = get_text_input(sentences);
        last_sentence_index = delete_sentences(sentences, last_sentence_index);
        print_text_after_work(sentences, last_sentence_index);
        break;
    case 4:
        last_sentence_index = get_text_input(sentences);
        sort_sentences(sentences, last_sentence_index);
        print_text_after_work(sentences, last_sentence_index);
        break;
    case 5:
        features_help();
        break;
    case 9:
        last_sentence_index = get_text_input(sentences);
        sort_words(sentences, last_sentence_index);
        break;
    default:
        print_error(2);
        break;
    }
}
