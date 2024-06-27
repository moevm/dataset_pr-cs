#include "Common.h"
#include "Function1.h"

CountWord* Function1(char** text, int* res) {
	int max_word = 50;
	int ptr_count = 0;
	int total_world = 0;
	CountWord* cs_wrd = malloc(sizeof(CountWord)* max_word);
	for (int i = 0; text[i] != NULL; i++) {
		char* sentens = text[i];
		char* ptr = strtok(sentens, " ,\t");
		
		while (ptr != NULL){
			ptr_count++;
			for (int j = 0; ptr[j] != '\0'; j++) {
				if (ptr[j] == '.') {
					ptr[j] = '\0';
					break;
				}
				ptr[j] = tolower(ptr[j]);
			}

			
			if (ptr_count >= max_word -1) {
				max_word += 50;
				cs_wrd = realloc(cs_wrd, sizeof(CountWord) * max_word);
			}
			
			int wordIndex = -1;
			for (int j = 0; j < total_world; j++) {
				if (strcmp(cs_wrd[j].word, ptr) == 0) {
					wordIndex = j;
					break;
				}
			}

			if (wordIndex != -1) {
				cs_wrd[wordIndex].count++;
			}
			else {
				cs_wrd[total_world].word = strdup(ptr);
				cs_wrd[total_world].count = 1;
				total_world++;
			}

			ptr = strtok(NULL, " ,\t");
		}
	}
	*res = total_world;
	return cs_wrd;
}