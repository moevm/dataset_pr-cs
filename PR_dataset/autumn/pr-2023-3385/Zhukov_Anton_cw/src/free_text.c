
#include <stdio.h>
#include <stdlib.h>

void free_text(char** text, int num_str) {
	if (text != NULL) {
		for (int i = 0; i < num_str; i++) {
			free(text[i]);
		}
		free(text);
	}
}
