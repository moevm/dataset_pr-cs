#include <stdio.h>
#include <stdlib.h>
#define MAX_STR 1000
#define MAX_STR_LEN 1000
#define END_STRING '\0'
#define FORBIDDEN_CHAR '7'

int end_text(char *current_sentence)
{
    char last_sentence[18] = "Dragon flew away!";
    for (int i = 0; i < 18; i++)
    {
        if (last_sentence[i] != current_sentence[i])
            return 1;
    }
    return 0;
}

void add_sentence (char **dyn_strs, int sentence_length, int* remaining_number_sentences, char* current_sentence)
{
    dyn_strs[*remaining_number_sentences] = (char *) malloc(sentence_length*sizeof (char));
    for (int j = 0; j < sentence_length; j++)
        dyn_strs[*remaining_number_sentences][j] = current_sentence[j];
    *remaining_number_sentences+=1;
}

void output (char **dyn_strs, int initial_number_sentences, int remaining_number_sentences)
{
    for (int i = 0; i < remaining_number_sentences; i++)
        puts (dyn_strs[i]);
    printf("Количество предложений до %d и количество предложений после %d",initial_number_sentences - 1, remaining_number_sentences - 1);
}

void free_memory (char **dyn_strs, int remaining_number_sentences)
{
    for (int i = 0; i < remaining_number_sentences; i++)
        free (dyn_strs[i]);
    free (dyn_strs);
}

void text_processing (char **dyn_strs, int *initial_number_sentences, int *remaining_number_sentences)
{
    char* current_sentence = (char *) malloc (MAX_STR_LEN * sizeof (char));
    while (end_text (current_sentence))
    {
        int sentence_length = -1, is_forbidden_char_in_sentence = 0;
        do
    	{
            sentence_length++;
        	if (sentence_length > 0 && (current_sentence[0] == '\t' || current_sentence[0] == ' '))
        	    sentence_length--;
        	scanf ("%c", &current_sentence[sentence_length]);
        	if (current_sentence[sentence_length] == FORBIDDEN_CHAR)
        	    is_forbidden_char_in_sentence = 1;
    	}while (current_sentence[sentence_length] != '.' && current_sentence[sentence_length] != ';' && current_sentence[sentence_length] != '?' && current_sentence[sentence_length] != '!');
        current_sentence[sentence_length + 1] = END_STRING;
        sentence_length+=2;
        if (is_forbidden_char_in_sentence == 0)
    	    add_sentence (dyn_strs, sentence_length, remaining_number_sentences, current_sentence);
        *initial_number_sentences+=1;
    }
    free (current_sentence);
}


int main()
{
    char **dyn_strs = (char **) malloc (MAX_STR * sizeof (char *));
    int initial_number_sentences = 0, remaining_number_sentences = 0;
    
    text_processing (dyn_strs, &initial_number_sentences, &remaining_number_sentences);
    output (dyn_strs, initial_number_sentences, remaining_number_sentences);
    free_memory (dyn_strs, remaining_number_sentences);
    return 0;
}
