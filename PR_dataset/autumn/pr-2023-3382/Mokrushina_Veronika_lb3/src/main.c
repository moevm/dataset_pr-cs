#include <stdio.h>
#include <string.h>
#include <malloc.h>

char* next_statement();
void print_statement(char* s);
int eto_konec(char* s);

int main() {
	int k = 0;
	for (int i = 0;; i++) {
		char* s = next_statement();
		if (s == NULL) {
			break;
		}
		char e = s[strlen(s) - 1];
		if (e != '?') {
			print_statement(s);
			k++;
		}
		if (eto_konec(s)) {
			printf("Количество предложений до %d и количество предложений после %d", i, k-1);
			free(s);
			break;
		}
		free(s);
	}
	return 0;
} 

char* next_statement() {
	int n = 100;
	char* buf = malloc(n);
	int i = 0;
	for (;;) {
		int c = getchar();
		if (c == EOF) {
			if (i == 0) {
				free(buf);
				return NULL;
			}
			if (i >= n) {
				n += 100;
				buf = realloc(buf, n);
			}
			buf[i] = '\0';
			return buf;
		}
		if (i >= n) {
			n += 100;
			buf = realloc(buf, n);
		}
		buf[i] = c;
		i++;
		switch (c) {
			case '.':
			case ';':
			case '?':
			case '!': 
				if (i >= n) {
					n += 100;
					buf = realloc(buf, n);
				}
				buf[i] = '\0';
				return buf;
		}
	}
}

void print_statement(char* s) {
	while (*s == '\t' || *s == ' ' || *s == '\n') {
		++s;
	}
	printf("%s\n", s);
 }

int eto_konec(char* s) {
	while (*s == '\t' || *s == ' ' || *s == '\n') {
		++s;
	}
	return strcmp(s, "Dragon flew away!") == 0;
}