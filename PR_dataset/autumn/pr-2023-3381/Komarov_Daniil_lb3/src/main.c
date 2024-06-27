#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int read_stdin(char** output)
{
	char* result = (char*) malloc(50);
	if(!result) {printf("Unable to allocate memory!"); exit(1);}
	int allocated_memory_size = 50;
	char ending[18];
	ending[17] = '\0';
	int result_len = 0;
	while(!(result_len >= 17 && strcmp(ending, "Dragon flew away!") == 0))
	{
		result[result_len] = getchar();
		result_len++;
		if(result_len >= 17) {memcpy(ending, &result[result_len-17], 17);}
		if(result_len == allocated_memory_size-1)
		{
			char* new_ptr = (char*)realloc(result, allocated_memory_size+50);
			if(new_ptr)
			{
				result = new_ptr;
				allocated_memory_size += 50;
			}
			else
			{
				printf("Unable to allocate memory!");
				exit(1);
			}
		}
	}
	*output = (char*)malloc(result_len);
	if(!output) {printf("Unable to allocate memory!"); exit(1);}
	memcpy(*output, result, result_len);
	free(result);
	return result_len;
}

int capital_letters_count(char* str)
{
	int count = 0;
	for(int i = 0; i < strlen(str); i++)
	{
		if(isupper(str[i])) {count++;}
	}
	return count;
}

int main()
{
	char* input;
	int input_len = read_stdin(&input);
	char* ptr_ending = &input[input_len];
	char* ptr_current = &input[0];

	char* sentence = (char*) malloc(50);
	char* ptr_sentence = &sentence[0];
	int allocated_memory_size = 50;

	int saved_sentences = 0;
	int all_sentences = 0;

	while(ptr_current != ptr_ending)
	{
		if(*ptr_current == '\n') {ptr_current++;} //skip all newlines
		else if((*ptr_current == ' ' && ptr_sentence == sentence)||(*(ptr_sentence-1) == ' ' && *ptr_current == ' ')) {ptr_current++;} //skip spaces at the beggining of the sentence and multiple spaces
		else if(*ptr_current == '.' || *ptr_current == ';' || *ptr_current == '?') //process sentence
		{
			int sentence_len = ptr_sentence - sentence; //real len + 1 for delimiter
			char* new_ptr_sentence = (char*) malloc(sentence_len + 2);
			if(!new_ptr_sentence) {printf("Unable to allocate memory!"); exit(1);}
			memcpy(new_ptr_sentence, sentence, sentence_len);
			new_ptr_sentence[sentence_len] = *(ptr_current++);
			new_ptr_sentence[sentence_len+1] = '\0';

			//read done, checking amount of capital letters and outputting
			int c = capital_letters_count(new_ptr_sentence);
			all_sentences++;
			if(c <= 1) {printf("%s\n", new_ptr_sentence); saved_sentences++;}

			sentence = (char*) realloc(sentence, 50);
			if(!sentence) {printf("Unable to allocate memory!"); exit(1);}
			ptr_sentence = &sentence[0];
			allocated_memory_size = 50;
		}
		else
		{
			int sentence_len = ptr_sentence - sentence - 1;
			if(sentence_len == allocated_memory_size)
			{
				sentence = (char*) realloc(sentence, allocated_memory_size+50);
				if(!sentence) {printf("Unable to allocate memory!"); exit(1);}	
				ptr_sentence = &sentence[sentence_len+1];
				allocated_memory_size += 50;
			}
			*(ptr_sentence++) = *(ptr_current++);
		}
	}
	//adding "Dragon flew away!" and footer
	printf("Dragon flew away!\n");
	printf("Количество предложений до %d и количество предложений после %d\n", all_sentences, saved_sentences);
}
