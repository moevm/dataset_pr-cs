
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int input_text(char*** main_text) {
	int volume_text = 50, volume_str = 50; 
	char** text = NULL;
	text = (char**)calloc(50, sizeof(char*));
	if (text == NULL) {
		printf("Error: Memory allocation error.\n");
		exit(1);
	}
	int num_str = 0, num_sym = 0;
	char check[2] = { getchar(), getchar() }; 

	while (check[0] != '\n' || check[1] != '\n') { 

		if (num_str + 1 == volume_text) { 
			volume_text += 50;
			if (text != NULL) {
				char** tmp = (char**)realloc(text, volume_text * sizeof(char*));
				if (tmp == NULL) {
					printf("Error: Memory expansion error.\n");
					exit(1);
				}
				else {
					text = tmp;
				}
			}
			else {
				printf("Error: Memory allocation error.\n");
				exit(1);
			}
		}

		if (text[num_str] == 0) { 
			volume_str = 50;
			text[num_str] = (char*)calloc(volume_str, sizeof(char));
			if (text[num_str] == NULL) {
				printf("Error: Memory allocation error.\n");
				exit(1);
			}
		}

		if (num_sym + 1 == volume_str) { 
			volume_str += 50;
			if (text[num_str] != NULL) {
				char* tmp = (char*)realloc(text[num_str], volume_str * sizeof(char));
				if (tmp == NULL) {
					printf("Error: Memory allocation error.\n");
					exit(1);
				}
				else {
					text[num_str] = tmp;
				}
			}
			else {
				printf("Error: Memory allocation error.\n");
				exit(1);
			}
		}

		if (!((check[0] == ' ' || check[0] == '\t' || check[0] == '\n') && (strlen(text[num_str]) == 0))) { 
			text[num_str][num_sym] = check[0];
			num_sym++;
		}

		if (check[0] == '.') { 
			text[num_str][num_sym] = '\0';
			num_str++;
			num_sym = 0;
		}
		check[0] = check[1];
		check[1] = getchar();
	}
	
	*main_text = text;
	return num_str;
}
