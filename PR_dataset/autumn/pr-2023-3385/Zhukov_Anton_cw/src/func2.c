
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void func2(char** text, int num_str) { 
	char* sentence;
	int num_sym;
	for (int i = 0; i < num_str; i++) {
		sentence = (char*)calloc(strlen(text[i]), sizeof(char));
		if (sentence == NULL) {
			printf("ERROR: Memory allocation error.\n");
			exit(1);
		}

		num_sym = 0;
		for (int j = strlen(text[i]) - 1; j >= 0; j--) {
			if (text[i][j] != ' ' && text[i][j] != '\t' && text[i][j] != '.' && text[i][j] != ',') {
				sentence[num_sym] = text[i][j];
				num_sym++;
			}
		}
		num_sym = 0;
		for (unsigned int j = 0; j < strlen(text[i]); j++) {
			if (text[i][j] != ' ' && text[i][j] != '\t' && text[i][j] != '.' && text[i][j] != ',') {
				text[i][j] = sentence[num_sym];
				num_sym++;
			}
		}
		free(sentence);
	}
}
