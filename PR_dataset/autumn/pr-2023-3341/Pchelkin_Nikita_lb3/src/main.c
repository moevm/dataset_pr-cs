#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>


char** input(char** text, int* size_of_text);
void reset_memory(char** text, int size_of_text);
void edit_n_out(char** text, int size_of_text, int* deleted);


int main()
{
	int size_of_text;
	char** text = input(text, &size_of_text);
	int deleted = 0;

	edit_n_out(text, size_of_text, &deleted);
	printf("Количество предложений до %d и количество предложений после %d", size_of_text-1, size_of_text-1-deleted);
	reset_memory(text, size_of_text);

	return 0;
}


char** input(char** text, int* size_of_text){
	int capacity_of_text = 1;
	text = (char**)malloc(sizeof(char*));
	char new_char = 'Z';
	(*size_of_text) = -1;
	int number_of_char;
	int capacity_of_sent = 1;	

	while(new_char != '!'){

		(*size_of_text)++;
		if((*size_of_text) + 1 > capacity_of_text){
			capacity_of_text *= 2;
			text = (char**)realloc(text, sizeof(char*)*capacity_of_text);
		}
		
		capacity_of_sent = 1;
		text[(*size_of_text)] = (char*)malloc(sizeof(char));
		number_of_char = -1;
		while(strchr(".;?!", new_char) == NULL){

			new_char = getchar();
			number_of_char++;
			if(number_of_char + 1 > capacity_of_sent){
				capacity_of_sent *= 2;
				text[(*size_of_text)] = (char*)realloc(text[(*size_of_text)], capacity_of_sent*sizeof(char));
			}
			
			text[(*size_of_text)][number_of_char] = new_char;
		}

		if (new_char != '!'){
			new_char = getchar();
		}
	}

	(*size_of_text)++;
	return text;
}


void reset_memory(char** text, int size_of_text){
	for(int i = 0; i < size_of_text; i++){
		free(text[i]);
	}
	free(text);
}


void edit_n_out(char** text, int size_of_text, int* deleted){
	int amount_of_upper_letters;
	for(int i = 0; i < size_of_text; i++){
		amount_of_upper_letters = 0;

		for(int x = 0; x  <= strpbrk(text[i], ".;?!") - text[i]; x++){

			if(isupper(text[i][x])){
				amount_of_upper_letters++;
				if(amount_of_upper_letters > 1){
					(*deleted)++;
					break;
				}
			}
		}


		if (amount_of_upper_letters < 2){
			for(int j = 0; j <= strpbrk(text[i], ".;?!") - text[i]; j++){
				printf("%c", text[i][j]);
			}
			printf("\n");
		}
	}
}
