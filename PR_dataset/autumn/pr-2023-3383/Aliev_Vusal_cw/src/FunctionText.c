#include "Common.h"
#include "FunctionText.h"

char** FunctionText(int* count_sent) {
	int lenght = 20, width = 20;
	char symbol;
	int end = 0;
	char** text = malloc(sizeof(char*) * lenght);
	*count_sent = 0;
	for (int N = 0;; N++) {
		while (strchr(" \t\n", symbol = getchar())) {
			if (symbol == '\n') {
				end++;
				if (end == 2) {
					return text;
				}
				continue;
			}
		}
		char* sentens = malloc(sizeof(char) * width);

		end = 0;
		int M = 0;
		for (; symbol != '.'; M++) {
			sentens[M] = symbol;

			if (M > width - 1) {
				width += 20;
				sentens = realloc(sentens, sizeof(char) * width);
			}
			symbol = getchar();
		}
		sentens[M] = '.';
		M++;
		if (M > width - 1) {
			width += 20;
			sentens = realloc(sentens, sizeof(char) * width);
		}
		sentens[M] = '\0';
		text[N] = sentens;
		(*count_sent)++;
		if (*count_sent >= lenght) {
			lenght += 20;
			text = realloc(text, sizeof(char*) * lenght);
		}
	}
}