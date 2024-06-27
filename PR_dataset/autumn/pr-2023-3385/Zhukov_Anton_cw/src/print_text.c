
#include <stdio.h>

void print_text(char** text, int num_str) {

	for (int i = 0; i < num_str; i++) {
		printf("%s\n", text[i]);
	}
}

