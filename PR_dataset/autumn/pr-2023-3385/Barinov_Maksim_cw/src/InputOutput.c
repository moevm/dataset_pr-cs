#include "InputOutput.h"

struct Sentence* ReadSentence(){
	wchar_t* string = (wchar_t*)malloc(size_block * sizeof(wchar_t));
	wchar_t  c = L' ';
	int i = 0, size = size_block, soes = 1, cntbn = 0;
	do {
		c = getwchar();
		if (isspace(c) && soes == 1) {
			if (c == '\n') cntbn++;
			if (cntbn >= 2) break;
			continue;
		}
		soes = 0;
		if (i + 1 >= size) {
			string = (wchar_t*) realloc(string, (i + 1) * sizeof(wchar_t) + size_block * sizeof(wchar_t));
			if (string == NULL) {
				wprintf(L"Error: Не удалось выделить память");
				free(string);
				exit(0);
			}
			size += size_block;
		}
		string[i] = c;
		i++;
	} while (c != L'.');
	struct Sentence* sentens = (struct Sentence*)malloc(sizeof(struct Sentence*));
	sentens->symbols = string;
	sentens->size = i;
	sentens->ends = cntbn;
	return sentens;
}

void OutSentence(struct Sentence* a) {
	wchar_t* s = a->symbols;
	int len = a->size;
	for (size_t i = 0; i < len; i++) {
		wprintf(L"%lc", s[i]);
	}
	wprintf(L"\n");
}

void OutText(struct Text* text) {
	for (int i = 0; i < text->cnt; i++) {
		OutSentence(text->sents[i]);
	}
}

struct Text* ReadText() {
	struct Sentence** sentens = (struct Sentence**) malloc(size_block * sizeof(struct Sentence*));
	for (size_t i = 0; i < size_block; i++) {
		sentens[i] = malloc(size_block * sizeof(struct Sentense*));
	}
	int stop = 0, i = 0, size = size_block;

	while(stop != 2) {
		struct Sentence* c = ReadSentence();
		if (i + 1 >= size) {
			sentens = realloc(sentens, (i + 1) * sizeof(struct Sentence*) + size_block*sizeof(struct Sentence*));
			if (sentens == NULL) {
				wprintf(L"Error: Не удалось выделить память");
				for (int j = 0; j < i; j++) {
					free(sentens[i]);
				}
				free(sentens);
				exit(0);
			}
			size += size_block;
		}

		if (c->ends != 2)sentens[i] = c;
		i++;
		stop = c->ends;
	}
	struct Text* text = (struct Text*) malloc(sizeof(struct Text*));
	text->sents = sentens;
	text->cnt = i - 1;
	if (text->cnt == 0) {
		wprintf(L"Error: текст не был введен, программа будет завершена\n");
		exit(0);
	}
	delDuplicate(text);
	return text;
}
