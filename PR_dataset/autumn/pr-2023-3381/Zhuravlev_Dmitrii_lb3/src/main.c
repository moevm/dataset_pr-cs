#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	int N = 10;

	char* sentence = (char*) malloc(N * sizeof(char));
	char ch;

	int chars = 0;
	int flag = 0;
	int removed = 0;
	int total = 0;

	while (1) {
		ch = getchar();
		if (chars == 0 && ch == '\t') continue;
		if (chars == 0 && ch == '\n') continue;
		if (chars == 0 && ch == ' ') continue;
		if (ch == '\n') ch = ' ';
		if (ch == '7') flag = 1;
		if (chars > N-1) {
			N += 10;
			sentence = (char*) realloc(sentence, sizeof(char)*N);
		}
		sentence[chars] = ch;
		chars += 1;
		
		if (ch == '.' || ch == ';' || ch == '?' || ch == '!') {
			sentence[chars] = 0;
			if (flag) {
				removed += 1;
			} else {
				printf("%s\n", sentence);
			}
			total += 1;

			if (strcmp("Dragon flew away!", sentence) == 0) {
				printf("Количество предложений до %d и количество предложений после %d\n", total-1, total-1-removed);
				break;
			}
			free(sentence);

			flag = 0;
			N = 10;
			sentence = (char*) malloc(N * sizeof(char));
			chars = 0;
		}
	};
	return 0;
}