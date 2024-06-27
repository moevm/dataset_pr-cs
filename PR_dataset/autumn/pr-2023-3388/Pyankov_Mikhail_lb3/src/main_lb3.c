#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define BASE_SIZE 200
#define STOP_SENTENCE "Dragon flew away!"
#define STR_END '\0'
#define DEL_STR_1 " 555 "
#define DEL_STR_2 "555 "
#define DEL_STR_3 " 555"

int sentence_check(char* sentence, int sentence_length)
{
    char** str = malloc(BASE_SIZE*sizeof(char*));
    str[0] = DEL_STR_1;
    str[1] = DEL_STR_2;
    str[2] = DEL_STR_3;
    for(int i = 0; i < sentence_length; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            if(!strncmp(sentence+(char)i, str[j], strlen(str[j]))&&!(j==2&&(sentence+(char)i)[strlen(str[j])]!='.'))
            return 0;
        }
    }
    return 1;
}

char** text_input(int* text_length, int* sentences_amount_before, int* sentences_amount_after)
{
    char symbol;
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
            symbol = (char)getchar();
            if(sentence_length>=BASE_SIZE*sentence_size_count)
            {
                sentence = realloc(sentence, (sentence_length+1+BASE_SIZE)*sizeof(char));
                sentence_size_count++;
            }
            if(symbol!='\n'&&!(symbol==' '&&sentence_length==0))
            {
                sentence[sentence_length] = symbol;
                sentence_length+=1;
            }
            if(symbol=='\n'&&(sentence[sentence_length-1]==','||sentence[sentence_length-1]!=' ')&&sentence_length!=0)
            {
                sentence[sentence_length] = ' ';
                sentence_length+=1;
            }
            if(symbol=='.'||symbol==';'||symbol=='?'||symbol=='!')
            {
                *sentences_amount_before+=1;
                sentence[sentence_length] = STR_END;
                break;
            }
        }
        if(*text_length>=BASE_SIZE*text_size_count)
        {
            text = realloc(text, (*text_length+1+BASE_SIZE)*sizeof(char*));
            text_size_count++;
        }
        if(sentence_check(sentence, sentence_length))
        {
            text[*text_length] = sentence;
            *text_length+=1;
            *sentences_amount_after+=1;
        }
        if(!strcmp(sentence, STOP_SENTENCE))
        return text;
    }
}

void output(char** text, int* text_length, int sentences_amount_before, int sentences_amount_after)
{
    for(int i = 0; i < *text_length; i++)
    {
        puts(text[i]);
    }
    printf("Количество предложений до %d и количество предложений после %d", sentences_amount_before-1, sentences_amount_after-1);
}

int main()
{
    int text_length = 0;
    int sentences_amount_before = 0;
    int sentences_amount_after = 0;
    char** text = text_input(&text_length, &sentences_amount_before, &sentences_amount_after);
    output(text, &text_length, sentences_amount_before, sentences_amount_after);
}