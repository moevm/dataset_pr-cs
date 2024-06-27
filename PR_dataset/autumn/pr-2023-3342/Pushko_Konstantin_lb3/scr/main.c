#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define LINE_BREAKER '\n'
#define END_OF_LINE '\0'
#define TABULATION '\t'


int is_two_big(char* sentence)
{
    int big_letter_count = 0;
    for (size_t i = 0; sentence[i]; i++)
    {
        if (isupper(sentence[i]))
            big_letter_count++;
    }
    if (big_letter_count > 1)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

char** input(int* initial_count, int* deleted_count)
{
    int sentence_number = 0;
    int current_text_size = 2;
    char** text = (char**)malloc(current_text_size * sizeof(char*));
    char symbol;

    do
    {

        int index = 0;

        int current_sentence_size = 2;
        char* current_sentence = (char*)malloc((current_sentence_size) * sizeof(char));

        do
        {
            symbol = getchar();

            if ((index == 0) && ((symbol == TABULATION) || (symbol == ' ') || (symbol == LINE_BREAKER)))
                continue;

            current_sentence[index] = symbol;
            current_sentence = (char*)realloc(current_sentence, (current_sentence_size) * sizeof(char));
            current_sentence_size++;
            index++;

        } while (symbol != ';' && symbol != '.' && symbol != '?' && symbol != '!');

        *initial_count+=1;
        current_sentence[index] = END_OF_LINE;


        if (is_two_big(current_sentence))
        {
            text[sentence_number] = current_sentence;
            sentence_number++;
        }
        else
        {
            *deleted_count+=1;
            free(current_sentence);
        }

        text = (char**)realloc(text, (current_text_size) * sizeof(char*));
        current_text_size++;

    } while (symbol != '!');
    return text;
}
void output(char** text, int initial_count ,int deleted_count)
{

    for (size_t i = 0; i < (initial_count - deleted_count); i++)
    {
        printf("%s\n", text[i]);
    }

    printf("Количество предложений до %d и количество предложений после %d", initial_count - 1, initial_count - deleted_count - 1);
}

int main()
{


    int initial_count = 0;
    int deleted_count = 0;
    char** text = input(&initial_count,&deleted_count);


    output(text,initial_count,deleted_count);


    for (size_t i = 0; i < (initial_count - deleted_count); i++)
    {
        free(text[i]);
    }
    free(text);

}