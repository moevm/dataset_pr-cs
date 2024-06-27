#include "Common.h"
#include "OutText.h"

void OutText(char** text) {
	for (int i = 0; text[i] != NULL; i++) {
		printf("%s\n", text[i]);
	}
}