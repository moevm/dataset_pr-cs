#include "Common.h"
#include "Function3.h"

void Function3(char** text) {
	for (int i = 0; text[i] != NULL;) {
		char* sentence = text[i];
		int hasComma = 0;

		for (int j = 0; sentence[j] != '\0'; j++) {
			if (sentence[j] == ',') {
				hasComma = 1;
				break;
			}
		}

		if (hasComma) {
			free(text[i]);

			for (int k = i; text[k] != NULL; k++) {
				text[k] = text[k + 1];
			}
		}
		else {
			i++;
		}
	}
}