#include<stdio.h>
#include<string.h>
#include<stdlib.h>
   
#define BASE_SIZE 200
#define STOP_SENTENCE "Dragon flew away!"
#define FINAL_STR '\0'
#define FIRST_STR_TO_DELETE " 555 "
#define SECOND_STR_TO_DELETE "555 "
#define THIRD_STR_TO_DELETE " 555"
#define or ||

int sentence_check(char* sentence, int sentence_length)
{
    const char* str[] = {FIRST_STR_TO_DELETE, SECOND_STR_TO_DELETE, THIRD_STR_TO_DELETE};
    const int str_count = sizeof(str) / sizeof(str[0]);
    
    for(int current_character = 0; current_character < sentence_length; current_character++)
    {
        for(int current_str = 0; current_str < str_count; current_str++)
        {
            if (!strncmp(&sentence[current_character], str[current_str], strlen(str[current_str]))) 
            {
                if (!(current_str == 2 && sentence[current_character + strlen(str[current_str])] != '.')) 
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

char** text_input(int* text_length, int* sentences_sum_before, int* sentences_sum_after)
{
    char sign;
    char* sentence;
    int sentence_length;
    int sentence_size_count;
    char** text = (char**)malloc(BASE_SIZE*sizeof(char*));
    int text_size_count = 1;
    
    while(1)
    {
        sentence = (char*)malloc(BASE_SIZE*sizeof(char));
        sentence_length = 0;
        sentence_size_count = 0;
        
        while(1)
        {
            sign = (char)getchar();

            if(sign == '\n' && (sentence[sentence_length - 1] == ',' or sentence[sentence_length - 1] != ' ') && sentence_length != 0)
            {
                sentence[sentence_length] = ' ';
                sentence_length += 1;
            }

            if(sentence_length >= BASE_SIZE * sentence_size_count)
            {
                sentence = realloc(sentence, (sentence_length + 1 + BASE_SIZE) * sizeof(char));
                sentence_size_count++;
            }

            if(sign != '\n' && !(sign == ' ' && sentence_length == 0))
            {
                sentence[sentence_length] = sign;
                sentence_length += 1;
            }
            
            if(sign == '.' or sign == ';' or sign == '?' or sign == '!')
            {
                (*sentences_sum_before)++;
                sentence[sentence_length] = FINAL_STR;
                break;
            }
        }
        
        if(*text_length >= BASE_SIZE * text_size_count)
        {
            text = realloc(text, (*text_length + 1 + BASE_SIZE) * sizeof(char*));
            text_size_count++;
        }
        
        if(sentence_check(sentence, sentence_length))
        {
            text[*text_length] = sentence;
            (*text_length)++;
            (*sentences_sum_after)++;
        }
        
        if(strcmp(sentence, STOP_SENTENCE) == 0)
            return text;
    }
}

void output(char** text, int text_length, int sentences_sum_before, int sentences_sum_after)
{
    int counter_for_while = 0;
    while (counter_for_while < text_length)
    {
        puts(text[counter_for_while]);
        counter_for_while++;
    }
    printf("Количество предложений до %d и количество предложений после %d", sentences_sum_before - 1, sentences_sum_after - 1);
}

int main()
{
    int sentences_sum_before = 0;
    int sentences_sum_after = 0;
    int text_length = 0;
    char** text = text_input(&text_length, &sentences_sum_before, &sentences_sum_after);
    output(text, text_length, sentences_sum_before, sentences_sum_after);
}
