#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *input(int *size, int *num_of_sentences){
	int allocated_memory = 1;
	char *text = (char*)malloc(sizeof(char));
	
	char ch = getchar();
	while(ch != '!'){
		text[*size] = ch;
		(*size)++;
		
		if((*size) >= allocated_memory){
			allocated_memory *= 2;
			text = (char*)realloc(text,allocated_memory * sizeof(char));
		}
		
		if(ch == '.' || ch == ';' || ch == '?'){
			(*num_of_sentences)++;
		}
		
		ch = getchar();
	}
	return text;
}

void punctuation_processing(char* text, char* punctuation, int size) {
    int j = 0;
    for (int i = 0; i < size - 1; i++) {
        if (text[i] == '.' || text[i] == ';' || text[i] == '?') {
            punctuation[j] = text[i];
            j++;
        }
    }
}

void text_processing(char *text, char **sentences){                            
	char* separator = ".;?";
    char* tmp;
    
    tmp = strtok(text, separator);
    
    int i = 0;
    while (tmp != NULL) {
    	while(*tmp == ' ' || *tmp == '\n'){
    		tmp++;
		}
    	
        sentences[i] = tmp;
        i++;
        tmp = strtok(NULL, separator);
    }
}

int check_sentence(char *sentence){
	int num_in_word = 0;
	int start_flag = 0, end_flag = 0;
	
    for (int i = 0; i < strlen(sentence); i++) {
        if(!isdigit(sentence[i])) start_flag = 1;
        if(sentence[i] == ' '){
        	start_flag = 0;
        	end_flag = 0;
		}
        if(start_flag && isdigit(sentence[i])) end_flag = 1;
        if(!isdigit(sentence[i]) && start_flag && end_flag) num_in_word++;
    }
    
    return (num_in_word == 0);
}

void output(char **sentences, char *punctuation, int num_of_sentences){
	int num_of_sentences_after_check = 0;
    for (int i = 0; i < num_of_sentences; i++) {        
        if (check_sentence(sentences[i])) {
            num_of_sentences_after_check++;
            printf("%s", sentences[i]);
            printf("%c\n",punctuation[i]);
    	}
    }
    printf("Dragon flew away!\n");
    printf("Количество предложений до %d и количество предложений после %d\n", num_of_sentences, num_of_sentences_after_check);
}

void free_memory(char *text, char *punctuation, char **sentences){
	free(text);
	free(punctuation);
	free(sentences);
}

int main() {
	int size = 0, num_of_sentences = 0;
	char *text = input(&size, &num_of_sentences);
	
	char* punctuation = malloc((num_of_sentences + 1) * sizeof(char));
    punctuation_processing(text, punctuation, size);
	
	char **sentences = (char**)malloc((num_of_sentences + 1) * sizeof(char*));
	text_processing(text, sentences);
	
	output(sentences, punctuation, num_of_sentences);
	free_memory(text, punctuation, sentences);
	
	return 0;
}