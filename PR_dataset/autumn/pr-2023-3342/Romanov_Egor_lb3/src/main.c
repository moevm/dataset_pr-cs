#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STOP_SENTENCE "Dragon flew away!"
#define OUTPUT_PATTERN "Количество предложений до %d и количество предложений после %d"


char **read_text(int *num_of_sentences);
void give_answer(char **text, int *num_of_sentences);
void clean_memory(char **text, int *num_of_sentences);

int main() {
    
    int num_of_sentences = 0;

    char **text = read_text(&num_of_sentences);

    give_answer(text, &num_of_sentences);

    clean_memory(text, &num_of_sentences);

    return 0;
}

char **read_text(int *num_of_sentences){
    const char dot = '.', semicolon = ';', question_mark = '?';
    char **text;
    int sentence_size = 0, sentence_capacity = 1,end_of_sentence_flag = 0;
    text = calloc(1,sizeof(char*));
    text[*num_of_sentences] = calloc(1,sizeof(char));
    char ch;    
    while (1) {
        ch = getchar();
        if ((ch == dot) || (ch == semicolon) || (ch == question_mark)){
            end_of_sentence_flag=1;
            text[*num_of_sentences] = realloc(text[*num_of_sentences], (sentence_capacity+1) * sizeof(char));
            text[*num_of_sentences][sentence_size] = ch;
            text[*num_of_sentences][sentence_size+1] = '\0';
            (*num_of_sentences)++;
            sentence_size=0;
            sentence_capacity = 1;
            text = (char**)realloc(text, ((*num_of_sentences)+1)*sizeof(char*));
            text[*num_of_sentences] = calloc(1,sizeof(char));
            continue;
        }
        if (end_of_sentence_flag){
            end_of_sentence_flag = 0;
            continue;
        }
        if ((ch == '\t') || (ch == '\n')){
            continue;
        }
        if (sentence_size == sentence_capacity) {
            sentence_capacity *= 2;
            text[*num_of_sentences] = realloc(text[*num_of_sentences], sentence_capacity * sizeof(char));
        }
        text[*num_of_sentences][sentence_size] = ch;
        sentence_size++;
        if(strstr(text[*num_of_sentences], STOP_SENTENCE) != NULL){
            text[*num_of_sentences] = realloc(text[*num_of_sentences], (sentence_size) * sizeof(char));
            text[*num_of_sentences][sentence_size] = '\0';
            return text;
        }
        

    }
}

void give_answer(char **text, int *num_of_sentences){
    int result_num_of_sentences = *num_of_sentences;
    for (size_t i =0;i<*num_of_sentences+1;i++){
        if (!(strchr(text[i], '?'))){
            printf("%s\n",text[i]);
        } else {
            result_num_of_sentences--;
        }
    }
    printf(OUTPUT_PATTERN, (*num_of_sentences), result_num_of_sentences);
}

void clean_memory(char **text, int *num_of_sentences){
    for (size_t i =0; i< *num_of_sentences;i++){
        free(text[i]);
    }
    free(text);
}
