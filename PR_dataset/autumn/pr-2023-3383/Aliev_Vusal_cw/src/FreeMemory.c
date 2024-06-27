#include "Common.h"
#include "FreeMemory.h"

void FreeMemory(char** text){
	for (int i = 0; text[i] != NULL; i++) {
		free(text[i]);
	}
	free(text);
}