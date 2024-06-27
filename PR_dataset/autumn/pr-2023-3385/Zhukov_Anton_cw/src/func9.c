#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void func9(char** text, int num_str, int count){
	for(int i=0; i < num_str; i++){
		char* sen = calloc(strlen(text[i])*(count+1), sizeof(char));
		if (sen == NULL){
			printf("Error: Memory allocation error.\n");
			exit(1);
		}
		for (int j = 0; j < count; j++){
			strcat(sen, text[i]);
			sen[strlen(sen)-1] = ' ';	
		}
		sen[strlen(sen) - 1] = '.';
		free(text[i]);
		text[i] = sen;
	}
}
