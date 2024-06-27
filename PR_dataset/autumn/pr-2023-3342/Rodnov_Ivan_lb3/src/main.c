#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define NULL_CHARACTER '\0'
#define TARGET_DIGIT '7'

bool contains_TARGET_DIGIT(char* sentence) {
    for (int i = 0; i < strlen(sentence); i++) {
        if (sentence[i] == TARGET_DIGIT) {
            return true;
        }
    }
    return false;
}

char* make_sentence()
{
    int sentence_len = 0;
    char curr_char;
    int curr_sentence_data = 10;
    char* sentence = malloc(sizeof(char) * curr_sentence_data);
    do
    {
        curr_char = getchar();
        if(isspace(curr_char) && sentence_len == 0){
            continue;
        }
        else{
            sentence[sentence_len] = curr_char;
            sentence_len++;
            if(sentence_len == curr_sentence_data - 1){
                curr_sentence_data *= 2;
                sentence = realloc(sentence, sizeof(char) * curr_sentence_data);
            }
        }
    }while(curr_char !='.' && curr_char !=';' && curr_char !='!' && curr_char != '?');
    sentence[sentence_len] = NULL_CHARACTER;
    return sentence;
}

char** make_text(int* text_len)
{
    int curr_text_data = 10;
    char* curr_sentence;
    char** text = malloc(sizeof(char*) * curr_text_data);
    do
    {   
        curr_sentence = make_sentence();
        text[(*text_len)++] = curr_sentence;
        if(*text_len == curr_text_data - 1){
            curr_text_data *= 2;
            text = realloc(text, sizeof(char*) * curr_text_data);
        }
    } while (strcmp(curr_sentence, "Dragon flew away!") != 0);
    return text;
}


void output(char** text, int* text_len, int* count_sentence_contains_target_digit)
{
    int size = 0;
    for(int i = 0; i < *text_len; i++){
        if(contains_TARGET_DIGIT(text[i])==false){
            printf("%s\n", text[i]);
            size++;
        }
        else{
            *count_sentence_contains_target_digit += 1;
        }
    }
    printf("Количество предложений до %d и количество предложений после %d\n", size + *count_sentence_contains_target_digit - 1, size - 1); 
}

int main()
{
    int text_len = 0;
    int count_sentence_contains_target_digit = 0;
    char** text = make_text(&text_len);
    output(text, &text_len, &count_sentence_contains_target_digit);
    for (int i = 0; i < text_len; i++) {
        free(text[i]);
    }
    free(text);
   
    return 0;
}
