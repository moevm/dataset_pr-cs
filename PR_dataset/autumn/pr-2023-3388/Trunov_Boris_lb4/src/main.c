#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define END_OF_STRING '\0'
#define LENGTH_STRING 1000
#define LENGTH_WORD 30
#define SEPARATOR " ."

int compare(const void* first, const void* second){
	const char ** first_word = (const char**)first;
	const char ** second_word = (const char**)second;
	return strcmp(*first_word, *second_word);
}

int compare_to_search(const void* key, const void* value){
	const char * found_word = (const char *)key;
	const char ** current_word = (const char **)value;
	return strcmp(found_word, *current_word);
}

void print_result(char ** result){
	if (result){
		printf("exists");
	}else{
		printf("doesn't exist");
	}
}

char ** fill_words(char ** words, char * text, size_t * count_words){
	char * current_word = strtok(text, SEPARATOR);
	while(current_word){
		words = realloc(words, sizeof(char*)*((*count_words) + 1));
		words[*count_words] = malloc(sizeof(char)*(strlen(current_word) + 1));
		words[*count_words] = strcpy(words[*count_words],current_word);
		*count_words += 1;
		current_word = strtok(NULL, SEPARATOR);
	}
	return words;
}

void free_memory(char ** words, size_t count_words){
	for (size_t i = 0; i < count_words; i++){
		free(words[i]);
	}
	free(words);
}

int main(){
	char text[LENGTH_STRING];
	fgets(text, LENGTH_STRING, stdin);
	text[strlen(text)-1] = END_OF_STRING;
	char found_word[LENGTH_WORD];
	scanf("%s", found_word);
	size_t count_words = 0;
	char ** words = malloc(sizeof(char*)*count_words);
	words = fill_words(words, text, &count_words);
	qsort(words, count_words, sizeof(char*), compare);
	char ** result = bsearch(found_word, words, count_words, sizeof(char*), compare_to_search);
	print_result(result);
	free_memory(words, count_words);
	return 0;
}
