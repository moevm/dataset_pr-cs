
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "print_text.h"
#include "free_text.h"

int func3(char*** main_text, int* main_num_str) {
	char** text = *main_text;
	int num_str = *main_num_str;
	char** new_text = (char**)calloc(num_str+1,sizeof(char*));
	if (new_text == NULL){
		printf("Error: Memory allocation error.\n");
		exit(1);
	}
	int num_new = 0;
	for (int i = 0; i < num_str; i++) {
		if (strstr(text[i], "physics") == NULL) {
			new_text[num_new] = (char*)calloc(strlen(text[i])+1,sizeof(char));
			if (new_text[num_new] == NULL){
				printf("Error: Memory allocation error.\n");
				exit(1);
			}
			strcpy(new_text[num_new], text[i]);
			num_new++;
		}
	}
	free_text(text, num_str);
	*main_text = new_text;
	*main_num_str = num_new;
}
