#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

void input_text(char* t, char* s);
unsigned split_text(const char* t, char** words);
int compar(const void* e1, const void* e2);


int main() {
	char text[1000], str[30];
	input_text(text, str);
	char* words[500];
	unsigned numwords = split_text(text, words);
	qsort(words, numwords, sizeof(words[0]), compar);
	const char* key = str;
	void* a=bsearch(&key, words, numwords, sizeof(words[0]), compar);
	if (a)
		printf("exists");
	else
		printf("doesn't exist");
	for (unsigned i = 0; i < numwords; i++) {
		free(words[i]);
	}
	return 0;
}

void input_text(char* t, char* s){
	for (int i = 0; i < 1000; i++) {
		int c = getchar();
		if (c == '\n') {
			t[i] = 0;
			break;
		}
		t[i] = c;
	}
	for (int i = 0; i < 30; i++) {
		int c = getchar();
		if (c == '\n'|| c==EOF) {
			s[i] = 0;
			break;
		}
		s[i] = c;
	}
	
}
unsigned split_text(const char* t, char** words) {
	unsigned k = 0;
	while (*t) {
		while (*t == ' ' || *t == '.')
			t++;
		if (*t == 0)
			break;
		char* u = strchr(t, ' ');
		char* y = strchr(t, '.');
		size_t l = 0;
		if (u == NULL && y == NULL)
			l = strlen(t);
		else if (u != NULL && y != NULL) {
			if (u > y)
				l = y - t;
			else
				l = u - t;
		}
		else if (u != NULL)
			l = u - t;
		else
			l = y - t;
		*words = malloc(l + 1);
		memcpy(*words, t, l);
		(*words)[l] = 0;
		words++;
		t += l;
		k++;
	}
	return k;
}

int compar(const void* e1, const void* e2) {
	const char* s1 = *(const char**)e1;
	const char* s2 = *(const char**)e2;
	return strcmp(s1, s2);
}
